<h1>ek-tm4c123gxl-boost-cc3100_basic_wifi_UDP Example</h1>

<!--##### README BEGIN #####-->
How and why to teach wireless connectivity


With all the buzz about the Internet of Things (IoT), we all have considered adding wireless connectivity to our embedded system lab. However, a flood of worries may hold us back, such as cost, complexity, and inertia.  This blog posts explains how and why I added an IEEE802.11 wireless lab to my embedded systems lab.

Why. With the proliferation of embedded systems and the pervasiveness of the internet, it is only natural to connect the two. IoT is the combination of embedded systems, which have sensors to collect data and actuators to affect the surrounding, and the internet, which provides for ubiquitous remote and secure communication. Traditional education on wireless communication focuses on the theory of communication, which is appropriate for those engineers destined to develop new channels and maintain existing ones. However, it is likely for the embedded system engineer to be asked to connect devices to the internet.  Therefore, we should add wireless connectivity to our students’ toolbox so they will be competitive in the job market.

Pedagogical Shift. I am a strong advocate of bottom-up education, which means we start with the basics, teach a topic until the student has full grasp, and then encapsulate and use that topic as we move to teach a higher-level topic. In order to connect to the internet, our device must implement a plethora of details to be fully compatible. The only way to add wireless to an existing embedded system lab is to violate the bottom up rule “students must understand everything about the devices they use” and provide them a working “black box” with which they can experiment. More specifically, we will purchase a hardware/software solution (called an internet stack) that is internet ready, and we will provide a rich set of example solutions to teach how the internet works at the component level. Students will modify and combine these examples to design systems. This purchase-and-use design process is prevalent in industry, so it will be beneficial for students to be exposed to both bottom-up and component-level design processes.

What. I added an IEEE802.11 lab where one microcontroller collects data, and a second microcontroller displays the data. Data are transmitted across a wireless network using UDP packets. I used two EK-TM4C123-GXL LaunchPads ($13 each), two CC3100 booster packs ($20 each), and a standard wireless access point ($30). This means the cost of entire lab is only $30+$66/team.
<youtube video of the system running>

How. The approach for implementing a smart object over wifi is to begin with a hardware/software platform that implements IEEE801.11 wifi. The CC3100BOOST is a boosterpack that can be used with the MSP430 LaunchPad, the TM4C123 LaunchPad, the TM4C1294 LaunchPad, or with a CC31XXEMUBOOST emulation module. The CC3100BOOST implements the internet stack with a combination of hardware and software components. Software in the LaunchPad preforms system calls to the CC3100BOOST to affect wireless communication. I didn’t use the CC31XXEMUBOOST emulation module because I didn’t want or need to reprogram the CC3100 boosterpack. In this lab students use two EK-TM4C123-GXL LaunchPads and develop a solution that transmits UDP packets from one smart object to another. UDP is simpler than TCP and appropriate for applications requiring simplicity and speed. Furthermore, to use UDP the application must tolerate lost or out of order packets. UDP provides a best-effort datagram delivery service.

I gave my students a starter project that implemented a simple communication channel and asked them to test this project and then to extend it to have more features. You need to first download and install Tivaware (http://www.ti.com/tool/sw-tm4c ). Find the directory with the examples\boards. E.g.,
C:\ti\TivaWare_C_Series-2.1.0.12573\examples\boards 

Next, you need to download this starter projects for the book at <web link>. Unzip these projects and place them into the Tivaware examples/board so the directory tree looks like this:
TivaWare_C_Series-2.1.0.12573
  examples
    boards
      CC31xxxx
        ek-tm4c1294xl-enet_uip_temperature
        ek-tm4c123gxl-boost-cc3100_basic_wifi_UDP 

To get the ek-tm4c123gxl-boost-cc3100_basic_wifi_UDP project to run, the first set of steps involve hardware devices:
0) First, you will need to configure a wireless access point as unencrypted. Give the AP a name. In the starter project you will notice my AP was called Valvano.
1) You will need to build hardware for the server. The server smart object includes a LaunchPad, a CC3100 booster, and an LCD display. I used the ST7335 color LCD from AdaFruit (http://www.adafruit.com/products/358).
2) You will need to build hardware for the client. The client smart object includes a LaunchPad, a CC3100 booster, and some sensor interface that creates an analog input on PD0. There is an option to stream simulated EKG if you do not wish to build external circuits for the client.

The second set of steps involves hardware testing and discovering the IP addresses of the two smart objects. Connect a CC3100 boosterpack to each LaunchPad and plug one LaunchPad USB into the PC. Using the device manager discover the COM port assigned to the LaunchPad. Then configure PuTTy to run at that COM port, 115200 bits/sec, 1 stop, no parity, and no flow control. The steps are:
1) Change line 59 in starter.c to match the name of your AP
#define SSID_NAME  "Valvano"          // Open AP name to connect to.
2) Edit lines 66,67,68 in the starter.c so the system interacts with an interpreter. Exactly one of these three #define statements should be true. 
#define SENSORNODE 0       // true if this node is sending UDP packets, using client
#define DISPLAYNODE 0      // true if this node is receiving UDP packets, using server
#define CRTNODE 1          // true if this node is runs an interpreter on UART0
Build the project, and download code to the LaunchPad. Start PuTTy and run the code. By observing PuTTy, you can test to see if the AP and LaunchPad/CC3100 can communicate. If you type ping<enter> then the smart object will ping the AP. Repeat this step 2 for the other smart object. The Dynamic Host Configuration Protocol server provides an IP address, and is typically initiated via a DHCP broadcast, when it connects. You need to determine the IP address for the server smart object. The Domain Name System (DNS) host can be used to translate domain names to IP addresses. However, for this simple example we will assume the IP address is on the local network and is fixed, so it can be hard-coded into the software.
3) Change the IP address to match the IP of your server, which is line 63 of starter.c. In my system the server has IP address 192.168.1.100.
#define IP_ADDR   0xc0a80164      // 192=0xC0, 168=0xa8, 0x01=1, 0x64 = 100
<youtube screen shot of debugging>

The third step is to edit, build and download server code to the server smart object. 
#define SENSORNODE 0       // true if this node is sending UDP packets, using client
#define DISPLAYNODE 1      // true if this node is receiving UDP packets, using server
#define CRTNODE 0          // true if this node is runs an interpreter on UART0
Look at how simple the server code is. 

The fourth step is to edit lines 63-70 of start.c, build and download client code to the client smart object. Set EKG to 1 for simulated ekg data, or set ADC to 1 for actual ADC measurements on Ain7 = PD0.
#define SENSORNODE 0       // true if this node is sending UDP packets, using client
#define DISPLAYNODE 1      // true if this node is receiving UDP packets, using server
#define CRTNODE 0          // true if this node is runs an interpreter on UART0
#define EKG 1              // client simulates ekg instead of measuring ADC
#define ADC 0              // client gets data from ADC, Ain7 = PD0

The client code is equally simple. Power up the AP and two smart objects and data will be collected on the client and sent to the server. The UDP payload can be seen in the uBuf[12] data structure (line 77 in start.c), which consists of message type, “=”, and ASCII string data representing the measured signal. main, main0, main1 and main2 are different versions with varying amounts of UART debugging output and error recovery.


For more information see Chapter 11 in Embedded Systems: Real-Time Interfacing to ARM Cortex-M Microcontrollers, 2014, ISBN: 978-1463590154, http://users.ece.utexas.edu/~valvano/arm/outline.htm 



Jonathan Valvano 8/1/2014
<!--##### README END #####-->

-------------------------------------------------------------------------------

Copyright (c) 2014 Texas Instruments Incorporated.  All rights reserved.
TI Information - Selective Disclosure
