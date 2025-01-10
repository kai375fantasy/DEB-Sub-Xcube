# Debugging & Logging Subsystem for XCube2D

This project is a Debugging & Logging subsystem designed as part of the CI517 module. It provides essential debugging tools for game engine development, including:
- Multi-level logging with dynamic filtering and log rotation.
- Global exception handling for runtime error tracking.
- Real-time FPS monitoring.
- Player movement debugging for input validation.

---

## **Features**
1. **Multi-level Logging**:
   - Supports `INFO`, `WARNING`, `ERROR`, `CRITICAL`, and `EASTER_EGG` levels.
   - Allows dynamic log filtering to control verbosity.
   - Automatically rotates logs to limit file growth.

2. **Global Exception Handling**:
   - Captures standard and unknown exceptions.
   - Logs errors as `CRITICAL` level events.

3. **FPS Monitoring**:
   - Displays real-time FPS on the game screen.

4. **Player Movement Debugging**:
   - Logs player input to verify movement logic and input accuracy.

---

## **How to Run**
1. Clone the repository:
   ```bash
   git clone https://github.com/kai375fantasy/DEB-Sub-Xcube.git
