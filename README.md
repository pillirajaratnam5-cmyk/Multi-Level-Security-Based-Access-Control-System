# Multi-Level-Security-Based-Access-Control-System


## Overview

The Multi-Level Security Based Access Control System is an embedded security application developed using the ARM7 LPC2124/LPC2129 microcontroller. The system implements a two-factor authentication mechanism consisting of Password Verification and OTP Verification to ensure secure access control.

Only authorized users who successfully pass both verification stages are granted access. The system provides visual feedback through LEDs and status messages on a 16x2 LCD display.

---

## Features

* Password-Based Authentication
* OTP-Based Secondary Verification
* Three OTP Retry Attempts
* Access Granted / Access Denied Status
* Wrong OTP Detection
* Red LED Alert for Invalid OTP
* LCD-Based User Interface
* Keypad-Based Input
* Embedded Security Implementation

---

## Hardware Components

* ARM7 LPC2124 / LPC2129 Microcontroller
* 4×4 Matrix Keypad
* 16×2 LCD Display
* EEPROM (24C04)
* Red LED
* Yellow LED
* Push Button Switch
* Resistor Pack
* Power Supply

---

## Software Tools

* Embedded C
* Keil uVision
* Proteus 8 Professional

---

## System Architecture

```text
          User
            │
            ▼
      4x4 Keypad
            │
            ▼
    ARM7 LPC2124/LPC2129
            │
   ┌────────┼────────┐
   ▼        ▼        ▼
 EEPROM    LCD      LEDs
   │                 │
   ▼                 ▼
Password       Status Indication

            ▼
      OTP Generation
            │
      Push Button
            │
            ▼
      OTP Verification
            │
    ┌───────┴────────┐
    ▼                ▼
Access Granted   Access Denied
```

---

## Authentication Workflow

### Step 1: Password Verification

* User enters the password using the keypad.
* System validates the password.
* If incorrect, the user is prompted to enter the password again.
* If correct, OTP verification begins.

### Step 2: OTP Generation

* User presses the push button.
* System generates an OTP.
* OTP is displayed for verification.

### Step 3: OTP Verification

* User enters the generated OTP.
* System compares the entered OTP with the generated OTP.

### Step 4: Access Decision

#### Correct OTP

* Access Granted message displayed.
* User authentication completed successfully.

#### Wrong OTP

* Red LED glows.
* OTP attempt counter increments.

### Step 5: Retry Control

* Maximum OTP attempts allowed: 3.
* After three failed attempts:

  * Authentication process resets.
  * User must re-enter the password.

---

```markdown
# Project Demonstration

## Password Entry

When the system starts, the user is prompted to enter a valid password using the 4x4 keypad.

<p align="center">
  <img src="images/password_entry.png" width="700">
</p>

---

## Wrong Password Attempt

If an incorrect password is entered, the Red LED glows and the system prompts the user to enter the password again.

<p align="center">
  <img src="images/wrong_password.png" width="700">
</p>

---

## Password Verification

When the entered password matches the stored credentials, the system proceeds to the OTP verification stage.

<p align="center">
  <img src="images/password_verification.png" width="700">
</p>

---

## OTP Generation

After successful password verification, the user presses the push button to generate an OTP.

<p align="center">
  <img src="images/otp_generation.png" width="700">
</p>

---

## OTP Entry

The user enters the generated OTP using the keypad for verification.

<p align="center">
  <img src="images/otp_entry.png" width="700">
</p>

---

## Wrong OTP Attempt

Whenever an incorrect OTP is entered, the Red LED glows indicating authentication failure.

<p align="center">
  <img src="images/wrong_otp.png" width="700">
</p>

---

## OTP Retry Attempt

The system allows a maximum of three OTP verification attempts before restarting the authentication process.

<p align="center">
  <img src="images/otp_retry.png" width="700">
</p>

---

## Access Granted

When both password and OTP verification are successful, access is granted to the authorized user.

<p align="center">
  <img src="images/access_granted.png" width="700">
</p>

---

## Access Denied

If all three OTP attempts fail, access is denied and the user must restart the authentication process by entering the password again.

<p align="center">
  <img src="images/access_denied.png" width="700">
</p>

## Pin Interfaces

| Peripheral  | Description          |
| ----------- | -------------------- |
| Keypad      | Password & OTP Input |
| LCD         | Status Display       |
| EEPROM      | Credential Storage   |
| Push Button | OTP Generation       |
| Red LED     | Wrong OTP Alert      |
| Yellow LED  | System Status        |

---

## Learning Outcomes

* Embedded C Programming
* ARM7 Microcontroller Programming
* Keypad Interfacing
* LCD Interfacing
* EEPROM Communication
* Embedded Security Systems
* OTP Authentication Logic
* Access Control Design

---

## Future Enhancements

* GSM-Based OTP Delivery
* Fingerprint Authentication
* RFID-Based Access Control
* Mobile App Integration
* IoT-Based Remote Monitoring
* Cloud Authentication

---

## Author

**Raja Ratnam Pilli**

Embedded Systems Engineer | Embedded C | ARM7 | IoT Enthusiast
