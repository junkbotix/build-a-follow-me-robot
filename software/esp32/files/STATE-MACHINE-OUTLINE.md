![Junkbotix Banner](./images/banner-1024px.jpg)

Check out the latest on this project and other tutorials at the [Junkbotix Channel](https://www.youtube.com/channel/UCNxQ47xBEYjD-mey_lxj9Aw) on Youtube!

<br>

## Follow-Me Robot Controller - State Machine Outline

Below you'll find various tables and pseudo-code for the workings of the state machine process that will control my implementation of my follow-me robot.

<br>

## State Machine Transitions

*Every state has a potential transition state, or stays at the current state, with the exception of HCF_HALT (which cannot transition to a new state and so the power must by cycled/reset)*

| Machine State | Transitions From | Transitions To
| ------------- | ---------------- | --------------
| WAIT_FOR_GPS (Initial) | HANDLE_INVALID_CREDS<br>HANDLE_INVALID_MESSAGE | WAIT_FOR_CLIENT_REQUEST
| WAIT_FOR_CLIENT_REQUEST | WAIT_FOR_GPS | GET_ONBOARD_GPS_DATA
| GET_ONBOARD_GPS_DATA | WAIT_FOR_CLIENT_REQUEST<br>HANDLE_MANUAL_CONTROL<br>HANDLE_MOVEMENT<br>HANDLE_ARRIVAL | VALIDATE_CREDS
| VALIDATE_CREDS | GET_ONBOARD_GPS_DATA  | HANDLE_INVALID_CREDS<br>HANDLE_CURRENT_MESSAGE
| HANDLE_INVALID_CREDS | VALIDATE_CREDS | WAIT_FOR_GPS
| HANDLE_CURRENT_MESSAGE | VALIDATE_CREDS | HANDLE_INVALID_MESSAGE<br>HANDLE_POSITION_UPDATE<br>HANDLE_MANUAL_CONTROL
| HANDLE_INVALID_MESSAGE | HANDLE_CURRENT_MESSAGE | WAIT_FOR_GPS
| HANDLE_POSITION_UPDATE | HANDLE_CURRENT_MESSAGE | HANDLE_NAVIGATION
| HANDLE_MANUAL_CONTROL | HANDLE_CURRENT_MESSAGE | GET_ONBOARD_GPS_DATA<br>HCF_HALT
| HANDLE_NAVIGATION | HANDLE_POSITION_UPDATE | HANDLE_MOVEMENT<br>HANDLE_ARRIVAL
| HANDLE_MOVEMENT | HANDLE_NAVIGATION | GET_ONBOARD_GPS_DATA
| HANDLE_ARRIVAL | HANDLE_NAVIGATION | GET_ONBOARD_GPS_DATA
| HCF_HALT | HANDLE_MANUAL_CONTROL | NONE

<br>

## Default and Client Browser Messages

| Type | Description
| ---- | -----------
| NO_MESSAGE | Default message
| POSITION_UPDATE | From client browser, sent once per second, lat/lon/bearing
| MANUAL_CONTROL | From client browser, sent ad-hoc, per user selection

<br>

## Robot Server Responses

| Type | Description
| ---- | -----------
| Controller Page | HTML/CSS/JS for client (browser controller)
| VALID_CREDENTIALS | Sent back when credentials on controller page match on-board values
| INVALID_CREDENTIALS | Sent back when credentials on controller page does not match on-board values
| INVALID_MESSAGE | Sent back when the message received doesn't match valid message types: NO_MESSAGE, POSITION_UPDATE, MANUAL_CONTROL
| NAVIGATING_MESSAGE | Sent back when the robot is navigating to the client's position
| MANUAL_CONTROL_MESSAGE | Sent back when the client is using the manual controls 
| E_STOP_MESSAGE | Sent back when the client manual control selected is the emergency stop button
| ARRIVAL_MESSAGE | Sent back when the robot arrives at the client's location

<br>

## State Machine Pseudo Code

```
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Init:
    Turn off motors
    Turn off beacons
    Set State WAIT_FOR_GPS
    Exit

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Main Loop:

    State WAIT_FOR_GPS:

        Valid GPS:            
            Flash/Beep Beacons 2x
            Set State WAIT_FOR_CLIENT_REQUEST

        !Valid GPS:
            Fade in/out LED Beacon (LED breathing)

        Exit

    State WAIT_FOR_CLIENT_REQUEST:
        Controller Page Requested:
            Send client browser Controller page
            Set Current Message (NO_MESSAGE)
            Set State GET_ONBOARD_GPS_DATA

        !Requested:
            Fade in/out LED Beacon (LED breathing)
        
        Exit

    State GET_ONBOARD_GPS_DATA:
        Save GPS Data (use running average filter for each):
            Latitude
            Longitude
            Heading 

        Get Current Message

        If Message Received:
            Set State VALIDATE_CREDS
            Save Message as Current Message

        Exit

    State VALIDATE_CREDS:
        Set State HANDLE_INVALID_CREDS

        Get Credentials (from Current Message)

        If Valid Credentials:
            Send Response VALID_CREDENTIALS
            Set State HANDLE_CURRENT_MESSAGE

        Exit

    State HANDLE_INVALID_CREDS:
        Send Response INVALID_CREDENTIALS
        Set State WAIT_FOR_GPS
        Exit

    State HANDLE_CURRENT_MESSAGE:
        Set State HANDLE_INVALID_MESSAGE

        If Message == POSITION_UPDATE:
            Set State HANDLE_POSITION_UPDATE

        If Message == MANUAL_CONTROL:
            Set State HANDLE_MANUAL_CONTROL

        Exit

    State HANDLE_INVALID_MESSAGE:
        Send Response INVALID_MESSAGE
        Set State WAIT_FOR_GPS
        Exit

    State HANDLE_POSITION_UPDATE:
        Save Client Latitude/Longitude/Heading from Message
        Send Response NAVIGATING_MESSAGE
        Set State HANDLE_NAVIGATION
        Exit

    State HANDLE_MANUAL_CONTROL:
        Set State GET_ONBOARD_GPS_DATA

        Save Command from Message
        Send Response MANUAL_CONTROL_MESSAGE

        If Command == E_STOP:
            Send Response E_STOP_MESSAGE
            Set State HCF_HALT

        Exit

        # Potential future manual control Commands:

        # Stop 
        # Blink 
        # Beep

        # Forward/Right
        # Forward
        # Forward/Left

        # Reverse/Right
        # Reverse
        # Reverse/Left

    State HANDLE_NAVIGATION:
        Set State HANDLE_MOVEMENT

        Get Robot GPS Data (Latitude, Longitude, Heading)
        
        Calculate Robot Heading and Distance from Robot to Client

        If Distance is under Threshold:
            Set State HANDLE_ARRIVAL

        Exit

    State HANDLE_MOVEMENT:
        Set Robot Motors to Move Toward Client Position
        Set State GET_ONBOARD_GPS_DATA
        Exit

    State HANDLE_ARRIVAL:
        Send Response ARRIVAL_MESSAGE
        Flash/Beep Beacons 4x
        Turn off motors
        Turn off beacons
        Set State GET_ONBOARD_GPS_DATA
        Exit

    State HCF_HALT:
        Turn off motors
        Turn off beacons
        Exit
        # At this point power must be cycled (reset)
```