/*! \mainpage Description
 * 
 * The firmware is written in C using the Microchip MPLAB IDE.  The MPLAB Harmony 
 * Configurator is also used to generate code to configure the various peripherals 
 * and settings needed for the microcontroller to function correctly.  The code is 
 * written to the MISRA 2012 standard and has been static tested using 
 * the LDRA test software.  All of the functions used are arranged as tasks.  These 
 * tasks are state machines that govern the operation of a given task.  All tasks are 
 * broken up into appropriate states that allow other tasks to operate while waiting 
 * for an operation to complete.   Some states make use of local functions to make 
 * the state machine easier to view. When the system powers up, it goes through a 
 * self test and an initialization process and ensures that all functions are 
 * operational. The system is then ready for use. 
 * 
 * <B>MAIN:</B>
 * 
 * The starting point of the program.  The system tests are performed before any 
 * initialization takes place. After the system tests, the peripherals and  
 * application initializations take place.  Finally, the application tasks are used 
 * in a while loop.
 *
 * The tasks monitor currents and voltages at various points, provide a means for 
 * communicating with PerfSwitches or similar devices, as well as responding to 
 * commands from a host. 
 * 
 * The primary communication port to the host is USB.  The system is configured to 
 * use a WinUSB connection. A secondary UART connection is also available for testing 
 * and debugging code. All commands use a CRC to validate the command string and 
 * response.
 * 
 * The system uses two power supplies. One is a communication supply used to power 
 * the PerfSwitch or similar devices when they being tested or configured.
 * The second is a shooting power supply that is used to provide the energy needed
 * to ignite a detonator while a tool string is downhole.  The voltage and current 
 * for these supplies is monitored and the supplies can be turned off if an overvoltage
 * or overcurrent condition occurs. The supplies can also be set to a given voltage 
 * and can be turned on and off as needed. 
 *  
 * <B>TIMER:</B>
 * 
 * The TIMER task is used to maintain a 100uS timer tick.  This task uses the TIMER 
 * 1 instance. This tick is then used to generate 1mS, 10mS, 100mS and 1s ticks. 
 * Timer ticks needed for other tasks are generated here. 
 *   
 * <B>SWITCH:</B>
 * 
 * The SWITCH task monitors the front panel switches and generates commands to
 * actuate relays as required. Logic is also in place to prevent some 
 * switch actions based on other switch actions or positions. The switch positions 
 * are stored for retrieval from the host.
 * 
 * <B>COMM:</B>
 * 
 * The COMM task handles communications to the host either via a UART or USB connection.
 * Once a command is received, it is validated. If it is a valid command, flags are set
 * to begin processing the command and this machine waits for the command to complete.
 * Once the command processing is completed, the response is sent back to the host 
 * via the same connection the command was received.Once a response has been sent, 
 * this machine waits for another command.
 * 
 * <B>COMMAND:</B>
 * 
 * The COMMAND task responds when the COMM task sets a flag after receiving a valid 
 * command from the host. The CRC of the command is checked and if it is valid, the 
 * command is executed. There are two different types of commands that can be sent, 
 * protocol A.  Protocol A commands are commands for controlling the 
 * LIB or the system itself. Some protocol A commands are involved in the automated
 * operation of the PIB. These protocols are defined elsewhere. Once a command
 * is executed, a response is generated for transmission back to the host. Afterwards,
 * another command can be executed.  Only one command can be processed at a time. 
 *  
 * <B>USB:</B>
 * 
 * The USB task handles USB communications from the host.  It uses a WinUSB connection
 * and operates at full speed.  The full speed limitation is due to the hardware 
 * isolated USB connection. The data from the USB transfers are sent to the Rx and Tx
 * Fifos and then controlled by the COMM task to process the command. 
 * 
 * <B>UART:</B>
 * 
 * The UART task handles UART communications from the host.  This was used during the 
 * initial code development.  The settings are 115200-N-8-1. The data from the UART
 * transfers are sent to the Rx and Tx Fifos and then controlled by the COMM task to 
 * process the command. This port is now used to update the system firmware in a 
 * bootloader.
 * 
 * <B>CF:</B>
 * 
 * The CF task monitors the wire line current when the panel is in the ARM_CF function. 
 * Once started, the CF operation is governed by the new data flag generated in the 
 * ADC portion of system_interrupt.c.
 *
 * <B>SYSTEM_OKAY:</B>
 * 
 * This task checks the results of the Class B system tests performed by the main 
 * controller and the HVPS self test function.  If either one of the system tests fail, 
 * the DUMP LED is turned on to indicate a failure.
 *  
 * <B>crc:</B>
 * 
 * These functions calculate the CRC used to verify communications between the host and 
 * the panel as well as the panel and the PerfSwitches.  
 * 
 * <B>fifo:</B>
 * 
 * These functions transfer data into receive and transmit Fifos.  These Fifos ensure 
 * data is handled correctly to minimize data transmission errors. 
 * 
 * <B>statusst:</B>
 * 
 * These functions handle setting and clearing the status bits for the panel as well as
 * arranging the status bits for both the panel and PerfSwitches for transmission to 
 * the host. *   
 *  
 * <B>TEST:</B>
 * 
 * The TEST task performs some of the Class B safety test on the controller prior to 
 * the controller being initialize for use in the program.  This test is only 
 * performed at startup. The result of this test is used in the SYSTEM_OKAY task.
 *
 * <B>GAMMA:</B>
 * 
 * This task tracks the counts from the gamma detector. When a transition from the 
 * gamma detector is detected, a flag is set in system interrupt. One gamma count 
 * causes two interrupts. This is accounted for. The count is then transferred to the 
 * REPORT array for later transmission to the host.  The gamma gain circuit can be
 * adjusted by pushing the STATUS LED button.  Ten gain choices are available.  The
 * choice is stored in the controller memory.  See nvm_fs.c.
 * 
 * <B>GPT:</B>
 * 
 * This task decodes the Titan telemetry message from the GPT tool. Sync pulses 
 * occur every 64mS to indicate the start of a new data string. 21 'channels' of 
 * data can be sent along with a checksum and tool version number. The tool uses 
 * Titan telemetry protocol. Each bit uses a 200uS window. A data pulse received 
 * represents a 'one' and no data pulse represents a 'zero'. The states are configured 
 * so that other system tasks can be maintained while these tasks are waiting for an 
 * event to occur.
 * 
 * <B>HIGH SIDE:</B>
 * 
 * This task monitor the HST communication when the front panel knob is in the 
 * HIGH SIDE position. A UART is configured for 20KBaud N-8-1 to receive the data. 
 * These functions monitor the HST communication. A UART is configured to receive the 
 * data. This machine reads data from the UART and puts it to the RxFifo for later use. 
 * The first 30 transmissions from the HSI tool are the 'Sign On' data that includes 
 * the Tool ID and firmware version. All transmissions afterwards are the tool data 
 * values.
 * 
 * <B> NVM:</B>
 * 
 * This task stores and retrieves the gamma gain setting. The gain setting is determined
 * by pushing the STATUS LED button. Doing so toggles the gamma gain circuit through 
 * ten settings.The setting is stored with each switch push. The setting is retrieved 
 * at power on. It uses the the FAT image created in nvm_disk_images.c to store the 
 * STATUS LED switch count.
 * 
 */

/*! \page Revision
 * 
 * <B>Revision 1.00</B>
 * 
 * This is the initial code used for the Floresville testing and sales demo. The 
 * project Panel Interface Board reflects this revision.
 * 
 * <B>Revision 1.01</B>
 * 
 * This revision resulted from the initial testing at Denver. The 
 * code updates were as follows:
 * 
 * - auto_cf.c 
 * 
 *      - Function AUTO_CF_Tasks in state AUTO_CF_STATE_CHECK. Added ability to 
 *        calculate wireline resistance to help determine if a shot has occurred.  
 *        It is looking for a 90 ohm change in resistance in successive readings. 
 *        The initial shot detection success rate was only approx. 60%.  This along 
 *        with reducing the current change threshold to 120mA from 200mA allowed the 
 *        code to properly respond to the recorded data.
 *      
 * - hvps.c
 * 
 *      - Function HVPS_Tasks in state HVPS_STATE_EVENT_CHECK. Ensure all auto_cf 
 *        variables are reset after a shot event occurs or if there was an error.
 * 
 * <B>Revision 1.02</B> 
 * 
 * This revision addresses issues found in further testing of revision 1.01. 
 *  
 * - auto_cf.c 
 * 
 *      - Function AUTO_CF_Tasks in state AUTO_CF_STATE_CHECK. Added further checks 
 *        to make sure shot detect is within time window and that ENABLE switch is 
 *        pushed. Clear all shot detect variables if not within window or ENABLE 
 *        switch is released.
 * 
 * - cf.c
 * 
 *      - Function CF_Tasks in state CF_STATE_INIT. Added code to initialize averaging 
 *        variables.
 *      
 *      - Function CF_Tasks in state CF_STATE_READ_I.  Added averaging code similar 
 *        to Wl_SPS current average to average 5 readings of CF_current. This 
 *        alleviated false one reading changes that tripped the shot detection limits.
 * 
 * - cf.h
 * 
 *      - Added variables to accommodate the CF_current averaging.
 * 
 * - hvps.c
 * 
 *      - Function HVPS_Tasks in state HVPS_STATE_CHECK_OVERCURRENT. Removed check for
 *        panel switch being in ARM_CF or AUTO ARM_CF mode to reset hvps current flag.
 *        This caused issues when a shot did not occur.
 * 
 *  <B>Revision 1.03</B> 
 * 
 * This revision addresses issues found in further testing of revision 1.02. 
 *  
 * - hvps.c
 * 
 *      - Function HVPS_Tasks in state HVPS_STATE_EVENT_CHECK. Moved statement to reset
 *        HV_PS.ramp_start flag to immediately after shot detection.  Keeps auto ramp 
 *        from occurring twice. 
 * 
 *  <B>Revision 1.04</B> 
 * 
 * This revision addresses issues found in further testing of revision 1.03. 
 *  
 * - man.c
 * 
 *      - Function Test_Manchester added function to return FSK to original value 
 *        after finding a switch. This is the same as the Verifire code. This helps 
 *        finding ver.1.8 switches especially.  The MAN Bias adjustments found in 
 *        the Verifire are not used here.  
 * 
 * - hvps.c
 * 
 *      - Function HVPS_Tasks in state HVPS_STATE_EVENT_CHECK. Moved statement to reset
 *        HV_PS.run_time_count to immediately after shot detection.  Ensures proper 
 *        count reset instead of waiting for WL_SPS to decay.
 *  
 * <B>Revision 1.05</B> 
 * 
 * This revision addresses issues found in further testing of revision 1.04. 
 *  
 * - man.c
 * 
 *      - Function Test_Manchester remove check for switch data command.  Always check
 *        switch status bits to ensure a good command response. Apply FSK change if 
 *        a bad command response is received.  
 * 
 *  <B>Revision 1.06</B> 
 * 
 * This revision addresses issues found in further testing of revision 1.05.  
 * PerfSwitch temperature testing while communicating with the panel showed extra FSK 
 * transmissions due the FSK reset from rev. 1.04. Testing showed this is not required
 * for good performance. 
 *  
 * - man.c
 * 
 *      - Function Test_Manchester remove FSK reset to original FSK after a good
 *        switch communication.  Remove CMD.switch status bit check flag.
 * 
 * <B>Revision 1.107</B>
 * 
 * Update to change revision level meaning.   The whole part of the number represents 
 * the controller memory. 1 equals 512, 2 equals 1024, 3 equals 2048.  The fractional 
 * represents the code revision number. The rev number was changed to a 16 bit
 * number to accommodate the change. 
 * 
 * <B>Revision 1.108</B>
 * 
 * Update to change hvps_test.  No voltages are checked. This alleviates hardware 
 * variances causing random system check failures.
 * 
 * - hvps_test.c
 * 
 *      - Update HVPS_TEST_STATE_INIT_TEST state in HVPS_Test_Tasks function to skip to
 *        state HVPS_TEST_STATE_CHECK_TEST_DONE.  Test count has been updated to force 
 *        test to end properly so rest of program can continue.
 * 
 * <B>Revision 1.109</B>
 * 
 * Update to auto_cf to turn supply off if shooting current limit is reached.  
 * The same status bit for a shot detection is set.  This is read by the host. The host 
 * then checks if the switch actually fired. Also update to keep current less than 
 * shooting current while in ARM_CF and both buttons are used.  This keeps current from
 * trailing up is detonator resistance starts to drop.
 * 
 * - auto_cf.c
 * 
 *      - Update AUTO_CF_STATE_CHECK state to check if average current is greater than 
 *        the shooting current limit while in ARM_CF_AUTO. Set shot detection status 
 *        bit.  
 * 
 * - hvps.c 
 * 
 *      - Update HVPS_STATE_CHECK_OVERCURRENT state so HVPS control voltage is 
 *        decreased if the HV_PS current is greater than the shooting current limit
 *        while in ARM_CF and both the fire and enable buttons are used.  The control 
 *        voltage is then increased once the current is less than the shooting current 
 *        limit.  This keeps the current near the shooting current limit for the 
 *        duration of the shot window.
 * 
 * <B>Revision 1.110</B>
 * 
 * Update to auto_cf to disable shot detection when a power charge is being fired.
 * Two commands are added. Command 0x3B to disable shot detection; command 0x3C to 
 * enable shot detection. Shot detection is always enabled by default.
 * 
 * - auto_cf.c
 * 
 *      - Update AUTO_CF_STATE_WAIT state to add flag check for shot detection disable.
 * 
 * - commands.c 
 * 
 *      - Add two commands to accommodate the new feature. Command 0x3B disables shot
 *        detection.  Command 0x3c enables shot detection.  This must be used after a
 *        power charge is fired.  Shot detection is enabled by default at start up.
 * 
 * <B>Revision 1.111</B>
 * 
 * Update to switches to check if user releases the ENABLE button during a power charge 
 * shot.  If it is released, the status 2 bit is cleared to indicate this.  
 * 
 * - switches.c
 * 
 *      - Update the NO FIRE case in SW_COM.S1_state to check if it released during a
 *        power charge.  If so, clear the Status 2 bit.
 * 
 * <B>Revision 1.112</B>
 * 
 * Update to use STATUS front panel switch LED to indicate system problems instead of 
 * DUMP FIRE LED.  
 * 
 * - system_okay.c
 * 
 *      - Switch to STATUS_LED to indicate issue with system testing at startup.
 * 
 * - hvps.c
 * 
 *      - Switch to STATUS LED to indicate problem with HVPS supply.
 * 
 * - switches.c
 * 
 *      - Switch to STATUS LED to indicate problem with HVPS supply.
 * 
 * <B>Revision 1.113</B>
 * 
 * Update to create 1 second wait state after current spike or an HVPS is found.  Needed 
 * so HVPS can be reset properly by sending 0V control voltage.  Sending too soon allows 
 * HVPS to shutdown.  The wait state prevents that. 
 * 
 * - timers.c
 * 
 *      - Add 100mS HV_PS.spike_delay_tick.
 * 
 * - hvps.h
 * 
 *      - Add variables spike_delay_tick and spike_delay_count along with 
 *        HVPS_STATE_SPIKE_WAIT case.  These are used to control wait state.
 * 
 * - hvps.c
 * 
 *      - Add code in case HVPS_STATE_EVENT_CHECK to move to HVPS_STATE_SPIKE_WAIT 
 *        state when spike or timeout event has occurred.  HVPS_STATE_SPIKE_WAIT state
 *        creates a one second delay before moving on to send 0V control value to 
 *        HVPS DAC.   
 *
 * <B>Revision 1.114</B>
 * 
 * Update to use 4 to 20mA signal from APM voltmeter to calculate the WL_SPS voltage 
 * value.  For Rev. B PCBs and later.  Create WL_SPS_V function to convert the 4 to 20
 * mA signal to a voltage.  Also use flags to indicate that new hardware is present. 
 * This allows older boards to use this revision and later.
 * 
 *  - wl_sps_v.c and wl_sps_v.h
 * 
 *      -  New functions to convert the 4 to 20mA signal into a voltage that the panel 
 *         can use.
 * 
 *  - system_interrupt.c 
 * 
 *      - Add two ADC channels to accommodate the APM current input and a channel to 
 *        act as a switch to indicate that the new hardware is installed.
 * 
 *  - wl_sps.c
 * 
 *      - Add code in state WL_SPS_STATE_READ_V to check flag for new hardware.
 * 
 * <B>Revision 1.115</B>
 * 
 * Update to fix bug in over current control while in ARM mode.  Unit was not turning 
 * off supply correctly. Now unit performs as expected.  After overcurrent occurs, 
 * supply goes to minimum and STATUS LED stays lit until control pot is turned off.
 * 
 *  - switches.c 
 * 
 *      -  Update switch case ( SW_COM.S5_state ) for HVPS_ON to remove reset for 
 *         HV_PS.pot_switch to false.  
 * 
 *  - hvps.c
 * 
 *      - Remove extra flag check for HVPS control SPI write. This was causing the 
 *        system to occasionally hang if the flag was not cleared correctly.
 * 
 * <B>Revision 1.116</B>
 * 
 * Update to reduce voltage threshold for shot detection.  The voltage threshold 
 * is now 20V instead of 50V.  This is to accommodate the slower response time of the 
 * wire-line voltmeter.  The meter outputs approx. 30V instead of 50 to 60V that is
 * actually on the line.  This led to some missed shot detection. 
 * 
 *  - auto_cf.c 
 * 
 *      -  Update switch case ( AUTO_CF_STATE_WAIT.state ) for WL_SPS.voltage > 20U.  *        
 * 
 * <B>Revision 1.117</B>
 * 
 * Update to control HVPS turn off when in ARM mode.  This will alleviate unit 
 * sometimes locking up due to current/voltage spike that occurs when HVPS and DUMP 
 * FIRE relay opened when the ENABLE button was released and power was still applied to 
 * a load.  The unit now reduces the HVPS voltage to 35V before opening the two relays.
 * This prevents the spikes from occurring and the unit does not lock up.
 * 
 *  - switches.c
 * 
 *      - Update switch SW_COM.S1_state in case RLY_NO_FIRE. Remove turning off HVPS 
 *        and DUMP_FIRE relays.  Instead reset flag (HV_PS.fire_auto_run_flag) when in 
 *        ARM or ARM_CF modes and the ENABLE button has been released.  This flag is 
 *        used in hvps.c turn properly turn off the HVPS before opening the relays.
 * 
 *  - hvps.c
 * 
 *      - Update to function HVPS_Tasks.  Update switch case HVPS_STATE_SHUTDOWN_CHECK
 *        to turn off HVPS and DUMP_FIRE relays when the wire-line voltage is less 
 *        than 40V. This keeps spikes from occurring.
 * 
 *      - Update to switch case HVPS_STATE_EVENT_CHECK. Do not use HVPS wait when in 
 *        ARM mode. The WAIT is only needed in ARM_CF or AUTO_CF.
 * 
 * <B>Revision 1.118</B>
 * 
 * Update to reduce the rate the voltage changes to maintain a given plug current.  
 * This is hoped to alleviate current spikes during Recon plug shoots.  Also disable 
 * software overcurrent checks during plug shoot.
 * 
 *  - hvps.c 
 * 
 *      -  Update switch case ( HVPS_STATE_CHECK_OVERCURRENT.state ) so the increase
 *         rates are at 1500 instead of 100.  This slows the increase rate down.
 * 
 *      -  Function Set_HVPS_Ramp_Rate.  Store programmed increase rate to use after 
 *         plug shot is completed.
 * 
 *      -  Function HVPS_Tasks in switch case HVPS_STATE_SHUTDOWN_CHECK. Restore 
 *         original updates rates after plug shoot.
 * 
 *      -  Function HVPS_Tasks in switch case HVPS_STATE_EVENT_CHECK. Restore 
 *         original updates rates after plug shoot.
 * 
 *      -  Function HVPS_Tasks in switch case HVPS_STATE_CHECK_OVERCURRENT. Change 
 *         update rates to slow increase and raise decrease to try and alleviate 
 *         current spikes during plug shoot. Also, add check to disable overcurrent
 *         flag during plug shoot.
 * 
 *  - wl_sps.c
 * 
 *      -  Function WL_SPS_Tasks in switch case WL_SPS_STATE_CHECK_OVERCURRENT.  Add
 *         check to disable overcurrent flag during plug shoot.
 * 
 *  - cf.c
 * 
 *      -  Function CF_Tasks in switch case CF_STATE_CHECK_OVERCURRENT.  Add
 *         check to disable overcurrent flag during plug shoot.
 * 
 *  - switches.c
 * 
 *      -  Function execute switches in switch case SW_COM.S5_state (HVPS_OFF).  Add
 *         check to turn off relays if plug shoot is not occurring.
 *         
 * <B>Revision 1.119</B>
 * 
 * Update to fix erroneous message errors with some switch combinations.  Found that 
 * using Rev. 2.1 V3 switch after a safety sub did not allow the deto to be read 
 * properly.  Found that the Manchester Bias DAC voltage need to be increased to allow 
 * the deto to be read properly. Implemented similar method from old panel. Reviewed 
 * old panel code and also updated the method to modify the FSK signals for use over 
 * temperature.  
 * 
 *  - fsk.c  
 * 
 *      - Update function Generate_Sine_Wave_Data to vary the spacing between FSK DAC 
 *        updates by a variable amount instead a constant fixed amount based on the 
 *        switch preamble time response. This will account for fractional time changes
 *        more accurately.
 * 
 *  - man.c 
 * 
 *      - Update function Calc_Auto_Bias to increase the DAC bias voltage for a given 
 *        wireline current. Also implement a straight line equation for the DAC value
 *        based on the wireline current.  This is similar to the old panel method. The 
 *        equation is based on emperical results.
 * 
 * NOTE:  This version has field issues with switch communication at Haliburton site. 
 *        This led to further investigations with versions with versions X.120 to X.123.
 *
 * <B>Revision 1.120</B>
 * 
 * Update to control HVPS turn off.  Found that some situations caused the HVPS to go 
 * into a lockout condition when the HVPS is turned off.  If the HVPS voltage change 
 * occurs too quickly, the HVPS goes into a lockout condition until it recovers.  This 
 * caused issues when using AUTO_CF as a gun was missed. A controlled turn off has been
 * implemented to keep the HVPS from seeing large changes on the output. 
 * 
 *  - switches.c  
 * 
 *      - Update function execute switches in switch (SW_COM.S1_state) case RLY_NO_FIRE
 *        to reinitialize HV_PS.fire_auto_run_flag.  Also reinitialize this flag in case
 *        RLY_FIRE.  Update switch (SW_COM.S5_state) case HVPS_OFF to modify logic
 *        when relays turn off.  Allows voltage to go to zero during plug shoot.
 * 
 *  - hvps.c 
 * 
 *      - Update function HVPS_Tasks in switch case HVPS_STATE_SHUTDOWN_CHECK to add 
 *        variables needed to properly power down HVPS after shutdown event has 
 *        occurred. Relays open after supply is less than 40V. Update switch case 
 *        HVPS_STATE_EVENT_CHECK to add check to go to power down when needed. Add
 *        variables to properly power down HVPS. Move WL_SPS check to outside event 
 *        check so unit can power down properly. Update case HVPS_STATE_CALC_SETTING to
 *        bypass getting HVPS control voltage when a run is complete.  Update case 
 *        HVPS_STATE_CHECK_OVERCURRENT for added check for run completion when HVPS 
 *        output needs to increase.  Update case HVPS_STATE_ABORT so HVPS can power 
 *        down correctly.
 * 
 * NOTE:  FSK was set back to VX.118 and the straight line MAN bis adj. remained.  Still
 *        had issues with reading switch V3 deto values after safety sub. VERSION NOT 
 *        RELEASED.
 * 
 * <B>Revision 1.121</B>
 * 
 *        Kept FSK like VX.118 and tried MAN DAC bias values from old panel.  MAN DAC 
 *        bias results too low for proper operation.  VERSION NOT RELEASED.
 * 
 * <B>Revision 1.122</B> 
 * 
 *        Added additional MAN bias adj during FSK adjustment.  Changed MAN preamble
 *        time to account for long bit increase in switch.  Similar results with still
 *        bad results trying to read switch deto values after a safety sub.  VERSION 
 *        NOT RELEASED.
 * 
 * <B>Revision 1.123</B> 
 * 
 *        Changed minimum Manchester bit time from 320uS to 1mS. This allowed proper 
 *        deto values to be read from switch V3 after a safety sub.  Temperature 
 *        testing also showed that the FSK shifts need to be limited to 2%.  This kept 
 *        changes reasonable based on Manchester counts.  Removed additional MAN bias 
 *        adjustment.  Also moved FSK baud value to 400Hz.
 * 
 *   - fsk.c  
 * 
 *      - Update function Init_FSK to change FSK.baud to 400Hz. Also tweak DAC counts 
 *        between FSK DAC updates, increasing mark and space counts by one. This lowers 
 *        FSK frequencies a little.
 * 
 *   - man.h 
 * 
 *      - Change ManHalfLower value to represent 1mS instead of 320uS. This helps system
 *        ignore current pulses during the switch deto resistance measurement.  That 
 *        measurement generates a 5mA current pulse that the system would sometimes 
 *        misread as a MAnchester response.  This caused comm. issues.
 * 
 *   - man.c
 * 
 *      - Update function Calc_Fsk_Scaling to limit the amount of change (2%)based on 
 *        the Manchester preamble response.  Excessive FSK changes could lead to comm. 
 *        errors. Remove Man.bias_adj introduced in V1.122 from functions 
 *        Test_Manchester and Calc_Auto_Bias. Remove MAN preamble bit time adjustment 
 *        in V1.122.  Move the MAN response timer count to the interrupt routine to 
 *        reduce possible count variations. Create MAN.timer_value variable to use count
 *        recorded in the interrupt routine.
 * 
 *   - system_interrupt.c
 * 
 *      - Add MAN.timer_value = DRV_TMR2_CounterValueGet(); to Port A change notice 
 *        routine for recording the Manchester bit times.
 */
/**************************************************************************************/
/* Descriptive File Name

  Company:
    Hunting Titan

  File Name:
    document.c

  Summary:
    This file provides doxygen with a description of the firmware.

  Description:
    This file provides doxygen with a description of the firmware.  No functioning code
    is used here.
 */

/***************************************************************************************
 End of File
 */
