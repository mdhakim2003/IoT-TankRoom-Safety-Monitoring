# IoT-Based Tank Room Safety and Inspection Monitoring System

## 📖 Overview
An IoT-based tank room safety and inspection monitoring system integrating environmental sensors, occupancy detection, distance and smoke monitoring, and PLC-based water level control. Real-time data is visualized on a dashboard, enabling safe inspections, automated alerts, and reliable tank operations.

---

## ✨ Features
- Continuous monitoring of temperature, humidity, light, and air quality  
- Occupancy detection to activate inspection mode when technicians enter  
- Distance sensor to ensure safe proximity to the tank during inspection  
- Smoke/gas detection with automatic alarm and ventilation fan activation  
- PLC-based water level monitoring and motor control (0–90% range)  
- Centralized dashboard for real-time data, alerts, and inspection status  
- Database integration for historical data storage and analysis  

---

## 🛠️ Hardware & Software Used
- Arduino Uno / compatible microcontroller  
- Sensors: Temperature, Humidity, Light, Distance, Smoke, Occupancy  
- PLC system for water level and motor control  
- Servo motor and ventilation fan  
- Node-RED for IoT flow and dashboard visualization  
- DBeaver / SQL database for sensor data storage  
- Python (Thonny) for data handling and analysis  

---

## ⚙️ System Architecture
1. **Environmental Monitoring (IoT)**  
   - Sensors track temperature, humidity, and light.  
   - Data sent to microcontroller and IoT platform.  

2. **Safety & Inspection Monitoring (IoT)**  
   - Occupancy sensor activates inspection mode.  
   - Distance sensor prevents unsafe proximity.  
   - Smoke sensor triggers alarm and ventilation fan.  

3. **Tank Control System (PLC)**  
   - PLC monitors water level (0–90%).  
   - Motor ON/OFF controlled automatically for safe operation.  

4. **Data Visualization & Dashboard**  
   - Node-RED dashboard displays sensor data, alerts, and motor state.  
   - Database stores sensor readings with timestamps for analysis.  

---

## 💻 Database Design
- **Stations**: Represents tank room or inspection area  
- **Sensors**: Stores sensor type, unit, and station location  
- **Sensor_Data**: Stores real-time sensor readings with timestamps  
- Relationships:  
  - One station → many sensors  
  - One sensor → many sensor data records  

---

## 🚀 Future Improvements
- Add IoT cloud integration for remote monitoring  
- Mobile app notifications for alerts and inspection status  
- AI-based predictive analytics for hazard prevention  
- Enhanced visualization with 3D dashboard or AR interface  

---

## 📊 Analytical Insights
- Water level and temperature trends ensure safe operating conditions  
- Smoke detection events compared with fan activation prove system efficiency  
- Occupancy tracking shows inspection frequency and technician activity  
- Motor utilization analysis confirms efficient pump operation  

---

## 📝 Conclusion
This project demonstrates how IoT and PLC integration can improve safety, inspection efficiency, and reliability in industrial tank rooms. Real-time dashboards, automated alerts, and historical data analysis reduce accident risks and enhance operational decision-making.
