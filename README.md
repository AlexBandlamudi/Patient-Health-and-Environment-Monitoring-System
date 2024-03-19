# Patient-Health-and-Environment-Monitoring-System

### In today’s digital and fast paced world, the intersection of Digital technology and Health care is crucial for the development of various innovative health care systems. The convergence of healthcare and environment monitoring has created a whole new chapter for comprehensive assessment of the patient. This paper introduces a novel and innovative device that seamlessly amalgamates patient health data with real time environment data. The device is triggered by a ultrasonic sensor for effortless present selection. The device incorporates state of the art sensors, that includes Max30102 Heart rate sensor,MLX90614 body temperature sensor, DHT11 for monitoring temperature and humidity, BMP180 pressure sensor, with NodeMCU microcontroller as its core component. This paper presents the architecture, implementation, and outcomes of the PHES and also highlights its potential to reshape the health care practices. The biomedical data that is obtained from the device is transmitted to the cloud in realtime. The “Blynk” cloud platform is utilized to monitor and store the information. In this way the paramedical staff/specialist can analyze and monitor the data anywhere as long as they have access to the cloud platform.

### The entire code is in the final.ino file.

### components required are : 
### Ultrasonic sensor, 16x2 LCD display, I2C module, DHT11 sensor, BMP180 sensor,  MAX30102 Heartrate sensor, MLX90614 Infrared temperature sensor

### cicruit diagram: 
![Picture1](https://github.com/AlexBandlamudi/Patient-Health-and-Environment-Monitoring-System/assets/111354340/eb535b51-51af-4b11-8ab8-2287fc907171)
.
### Working: 
### All the components are soldered on a General purpose PCB. When the user waves the hand in front of the ultrasonic sensor in range of 30cm to 25cm, The system start monitoring Room temperature
### When the user waves the hand in front of the ultrasonic sensor in range of 25cm to 20cm, The system start monitoring Room Humidity .
### When the user waves the hand in front of the ultrasonic sensor in range of 20cm to 15cm, The system start monitoring Room Pressure .
### When the user waves the hand in front of the ultrasonic sensor in range of 15cm to 7cm, The system start monitoring Heart rate of the user 
### When the user waves the hand in front of the ultrasonic sensor in range of 7cm to 0cm, The system start monitoring Body Temperature 
### When a particular preset is selected, the system automatically uploads the data to the Bylnk cloud so that the doctor can monitor the patient health and room conditions anywhere in the world with the help of Internet

### Final project: 
![Picture2](https://github.com/AlexBandlamudi/Patient-Health-and-Environment-Monitoring-System/assets/111354340/f5bc4225-37a4-4e0c-907b-b637c5031f4b)

### Blynk WebDashboard: 
![Picture3](https://github.com/AlexBandlamudi/Patient-Health-and-Environment-Monitoring-System/assets/111354340/8731925c-a2f7-4b30-abe4-c93a8614cbec)
