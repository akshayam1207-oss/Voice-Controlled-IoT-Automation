# Task 3: IFTTT + Adafruit IO — Voice-Controlled IoT Automation

## 📌 Project Overview

This project demonstrates voice-controlled IoT automation using Google Assistant, IFTTT, Adafruit IO, and an ESP32.

The objective is to control a relay-connected bulb using voice commands such as **“OK Google, activate lights on”** and **“OK Google, activate lights off.”**

The project reuses the ESP32, relay module, bulb, and Adafruit IO feed from Task 2. IFTTT connects Google Assistant to Adafruit IO, allowing voice commands to control the same device without changing the ESP32 hardware.

## 🎯 Objectives

- Control a bulb using voice commands.
- Connect Google Assistant to Adafruit IO through IFTTT.
- Understand trigger-and-action automation.
- Reuse the existing ESP32 MQTT subscription and relay-control logic.
- Test voice commands and dashboard control using the same Adafruit IO feed.

## 🧠 Concepts Used

### 1. IoT Automation

IoT automation allows a device to respond to an event without requiring someone to operate it manually.

In this project, a spoken command triggers a cloud-based action that changes the state of the bulb.

### 2. IFTTT

IFTTT stands for **If This Then That**. It connects online services using applets.

Each applet contains:
- **If This:** The trigger that starts the automation.
- **Then That:** The action performed after the trigger.

### 3. Adafruit IO

Adafruit IO acts as the cloud connection between IFTTT and the ESP32.

IFTTT sends a value to the `LED` feed, and the ESP32 receives the update through its existing Adafruit IO connection.

### 4. MQTT Communication

The ESP32 receives updates from the Adafruit IO feed and uses the received value to control the relay.

| Feed value | Expected action |
|---|---|
| `1` | Turn the bulb ON |
| `0` | Turn the bulb OFF |

## 🛠️ Hardware Requirements

- ESP32 development board
- 5V relay module
- Bulb and suitable holder
- Smartphone with Google Assistant
- Connecting wires

**Safety note:** A 230V AC bulb circuit can cause fatal electric shock. Mains wiring must be completed and checked by a qualified person using an appropriately rated, enclosed relay and insulated terminals. Disconnect power before any hardware work.

## 💻 Software and Services

- Arduino IDE
- IFTTT account
- Google Assistant
- Adafruit IO account
- Existing Adafruit IO `LED` feed
- Adafruit IO Arduino library
- Serial Monitor for debugging

## ⚙️ IFTTT Applet Configuration

Two applets are configured to control the bulb.

| Setting | Applet 1: Lights ON | Applet 2: Lights OFF |
|---|---|---|
| Trigger service | Google Assistant | Google Assistant |
| Trigger phrase | Activate lights on | Activate lights off |
| Action service | Adafruit IO | Adafruit IO |
| Feed | `LED` | `LED` |
| Value sent | `1` | `0` |
| Expected result | Bulb ON | Bulb OFF |

### Steps to Create the Applets

1. Create a new applet in IFTTT.
2. Select Google Assistant as the trigger service.
3. Choose the **Activate scene** trigger, as used in this project.
4. Enter the scene name, such as `lights on`.
5. Select Adafruit IO as the action service.
6. Choose the action to send data to an Adafruit IO feed.
7. Select the `LED` feed and configure the value as `1`.
8. Save the applet.
9. Repeat the process for `lights off`, sending the value `0`.

*Note: Available IFTTT triggers and actions may depend on the services and integrations currently supported by your account.*

## 🔄 System Data Flow

```text
Voice Command
     |
     v
Google Assistant
     |
     v
IFTTT Applet
     |
     v
Adafruit IO — LED Feed
     |
     v
ESP32
     |
     v
Relay Module
     |
     v
Bulb ON / OFF
```

The same Adafruit IO feed is used by both the dashboard and the voice-control applets. Therefore, the existing ESP32 code can process updates from either input source.

## 💻 ESP32 Source Code

The project reuses the ESP32 sketch from Task 2:

`task2_task3_mqtt_relay.ino`

The feed subscription and callback handle incoming updates:

```cpp
AdafruitIO_Feed *ledFeed = io.feed("LED");

void handleRelay(AdafruitIO_Data *data) {
  int value = data->toInt();

  Serial.print("Adafruit IO value: ");
  Serial.println(value);

  digitalWrite(RELAY_PIN, value == 1 ? HIGH : LOW);

  Serial.println(
    value == 1
      ? "Relay ON -> Bulb ON"
      : "Relay OFF -> Bulb OFF"
  );
}
```

The existing setup must also register the callback and maintain the Adafruit IO connection:

```cpp
ledFeed->onMessage(handleRelay);
```

```cpp
void loop() {
  io.run();
}
```

**Important:** These are the relevant code sections, not a complete standalone sketch. Use the complete Task 2 source file with its Wi-Fi configuration, Adafruit IO credentials, pin definitions, connection setup, and callback registration.

Keep real Wi-Fi passwords and Adafruit IO keys private. Use placeholders in the public repository.

## 📸 Screenshots and Project Evidence

Upload your actual Task 3 screenshots into the `screenshots/` folder using the filenames below.

### IFTTT Configuration

![Lights ON Trigger](screenshots/task3-photo3.jpeg)

*Configuring the lights-on scene.*

![Lights OFF Trigger](screenshots/task3-photo4.jpeg)

*Configuring the lights-off scene.*

![Lights ON Applet](screenshots/task3-photo5.jpeg)

*Completed applet for sending `1` to the LED feed.*

![Lights OFF Applet](screenshots/task3-photo6.jpeg)

*Completed applet for sending `0` to the LED feed.*

### Working Prototype

![ESP32 Serial Monitor and Bulb](screenshots/task3-photo7.jpeg)

*Serial Monitor and bulb showing the control result.*

![ESP32 Relay Setup](screenshots/task3-photo8.jpeg)


*Testing voice commands using Google Assistant.*

> **Note:** These image links will work only after you upload the corresponding image files into the `screenshots` folder.


## 🧪 Testing and Results

| Test | Expected result | Result reported in the project |
|---|---|---|
| Say “activate lights on” | Bulb turns ON | Switched ON within approximately 1–2 seconds |
| Say “activate lights off” | Bulb turns OFF | Switched OFF within approximately 1–2 seconds |
| Repeat the ON command | Bulb remains ON | Remained ON |
| Send rapid ON/OFF commands | Bulb follows the latest command | Followed commands with a short delay |
| Alternate between dashboard and voice | Both control the same feed | Both worked |
| Restart the ESP32 | Reconnect and respond | Reconnected and responded |
| Use mobile data on the phone | Voice automation still works with internet access | Worked during testing |

These are the results described in the project report.

## 🐛 Problems and Solutions

| Problem | Solution |
|---|---|
| Google Assistant could not find the scene | Checked that the spoken phrase matched the configured scene name |
| Applet ran but the bulb did not respond | Checked the Adafruit IO feed history and verified the feed name |
| Delay between speaking and bulb response | Recognized the delay associated with cloud-based communication |
| Separate ON and OFF actions were needed | Created two applets that send `1` and `0` |

## 📚 Key Learnings

- Learned how IFTTT connects online services through triggers and actions.
- Understood how Google Assistant can initiate an IoT action.
- Learned how Adafruit IO connects a cloud automation service to an ESP32.
- Reused the same feed for both dashboard and voice control.
- Understood the trade-off between convenient cloud access and response delay.
- Practised debugging by checking feed updates and hardware behaviour.

## 📝 Reflection

This project demonstrated how voice control can be added to an existing IoT system without changing its hardware or ESP32 program. Google Assistant provides the voice interface, IFTTT connects the services, and Adafruit IO passes the command to the ESP32. Reusing the same feed allows dashboard and voice commands to control the same device.

The project also highlighted the importance of protecting cloud credentials and handling mains-powered hardware safely.

## ✅ Result

A voice-controlled IoT automation system was implemented using the following sequence:

**Google Assistant → IFTTT → Adafruit IO → ESP32 → Relay → Bulb**

The system supports voice-based ON/OFF control while retaining the existing Adafruit IO dashboard functionality.

---

**Project:** IFTTT + Adafruit IO — Voice-Controlled IoT Automation  
**Platform:** ESP32  
**Communication:** MQTT via Adafruit IO  
**Automation:** IFTTT and Google Assistant
