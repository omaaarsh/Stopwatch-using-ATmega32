# Stopwatch-using-ATmega32
digital stopwatch** designed using **ATmega32** and simulated in **Proteus**! This project is part of Standard embedded systems course at **Edges For Training ** and it showcases several key features.

### 🔧 **Project Features:**
- **Reset Function:** Instantly resets the timer to zero using an external interrupt.

- **Pause & Resume Functions:** Utilize external interrupts to pause the stopwatch and resume it from the same point.

- **Mode Toggle:** Switch between **increment mode** (standard stopwatch) and **countdown mode**, with LED indicators to show the current mode.

- **Real-Time Adjustments:** Users can increment or decrement **hours**, **minutes**, and **seconds** using push buttons, even while the stopwatch is running.

### 💻 **Code Overview:**

- **main.c:**  
   This file handles the initialization of I/O ports, timers, and external interrupts. It also contains the main loop that continuously displays the time and checks for mode toggles and time adjustments.
  
- **time_management.c:**  
   Responsible for managing the current time and checking button presses for time adjustments and mode toggling. The file ensures that time increments and decrements are handled smoothly and within limits.

- **timer.c:**  
   Timer1 is configured in **CTC mode** (Clear Timer on Compare Match) with a prescaler of 1024, generating a 1 Hz clock tick. It also includes functions to stop and resume the timer when needed.

- **interrupts.c:**  
   This file manages **external interrupts** and the **Timer1 Compare Match interrupt**. It handles the countdown timer in countdown mode, and the pause, reset, and resume functionalities through INT0, INT1, and INT2 external interrupts.

### 🛠️ **Key Hardware & Software Components:**
- **ATmega32 Microcontroller**

- **7-Segment Display**: Used to display       the current time (hours, minutes, and   
seconds).

- **LED Indicators**: To indicate the current mode (increment or countdown).

- **Buzzer**: Activated when the countdown reaches zero.

- **Push Buttons**: For adjusting time and toggling modes.
