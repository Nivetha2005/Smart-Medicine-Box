# 💊 Smart Medicine Box

An IoT-based solution designed to ensure timely medication intake, especially for elderly and forgetful individuals.

## 📌 Abstract
The **Smart Medicine Box** is an intelligent medication management system that reminds users to take medicines, detects interaction via sensors, and alerts when refills are needed. It is powered by **ESP8266** and integrates with the **Blynk Cloud App** for real-time alerts and control.

---

## 🧠 Key Features

- 🔔 Real-time medication reminders using buzzer
- 👋 Hand detection via ultrasonic sensor (HC-SR04)
- 🔓 Automatic lid control using servo motor
- 🌐 Wi-Fi-based remote alerts using ESP8266 + Blynk
- 📦 Pill count tracking and refill alerts
- 📱 Simple and interactive Blynk mobile app

---

## 🛠 Components Used

| Component         | Purpose                              |
|------------------|--------------------------------------|
| ESP8266 NodeMCU   | Main microcontroller with Wi-Fi      |
| HC-SR04 Sensor    | Detects hand motion (≤ 30 cm)        |
| Servo Motor       | Opens/closes lid                     |
| Buzzer            | Provides audible alerts              |
| Blynk Cloud       | Manages schedule and notifications   |
| NTP Server        | Accurate time synchronization        |

---

## 🧪 Methodology

1. **Schedule**: Set medicine times via Blynk App.
2. **Alert**: Buzzer rings at the scheduled time.
3. **Detection**: Ultrasonic sensor detects hand motion.
4. **Action**: If detected, servo opens the box.
5. **Logging**: Logs whether medicine was taken.
6. **Refill**: When pills are low, refill alert is triggered.

### 🔢 Blynk Virtual Pins
- `V1` – Set Time  
- `V2` – Pill Count Management  
- `V3` – Notifications  

---

## 📈 Experimental Results

- ✅ Buzzer alerts triggered precisely on time
- ✅ Ultrasonic sensor reliably detected hand movement
- ✅ Servo motor smoothly opened/closed lid
- ✅ Pill count tracking and refill alert worked accurately
- ✅ Blynk app was user-friendly and responsive

---

## 🔮 Future Enhancements

- Multiple compartment management  
- AI-based dosage suggestions  
- Patient activity and medication compliance tracking  

---

## 👩‍💻 Contributors

- **Nivetha T** – 2022510007  
- **Jhanavi S** – 2022510020  
- **Jessica Katherine F** – 2022510021

---

## 📜 License

This project is open source and available under the [MIT License](LICENSE).
