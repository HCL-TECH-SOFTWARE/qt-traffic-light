# qt-traffic-light
## Use RTist in a Qt application
### System toolchain requirement
To test this scenario following setup is done.
1.	Qt 6.7 is installed on Windows machine with MinGW toolchain.
2.	RTist 11.3 product release is installed on Windows with Eclipse IDE 2022.06.

### Software reference
A sample Qt application has been developed based on the following open-source RTist sample:

https://github.com/HCL-TECH-SOFTWARE/traffic-light-web 

This sample uses a web page as its UI, and in the Qt application it has been replaced with a Qt UI based on the following sample from the Qt documentation:

https://doc.qt.io/qt-6/qtstatemachine-trafficlight-example.html

The state machine logic of this Qt sample was removed and replaced with the state machine of the RTist sample.

### How the Qt application works
We choose to let the main thread run the Qt UI. In main.cpp the QApplication is created with a main window. The main thread will then simply run the application’s event loop which handles all Qt UI events.

In the main window constructor (MainWindow.cpp) we create a QThread (MyThread.cpp) responsible for running the RTist part of the application. We use signals and slots as the means of communicating messages from the RTist part to the Qt UI.

When the QThread starts to run (function MyThread::run()) it will call RTMain::entryPoint() and then pass necessary arguments which otherwise is provided by the TargetRTS. In the sample these are the path to the Qt application and “-URTS_DEBUG=quit” (to not use the RTist debugger). Of course, you can pass any data needed by the RTist part of the application in a similar way, and this is just a minimal example.

The RTist part of the application is run by MyThread and uses a top capsule TLSystem with these capsule parts:
#### •	trafficLight
Implements the traffic light logic using an RTist state machine. This part is independent on Qt.
#### •	qtUI
Responsible for communication from the RTist part of the application to the Qt UI. When the red, green and yellow events arrive, the Qt application is notified by emitting the signals that were mapped in the MainWindow constructor. The mapped slot functions will then update the Qt UI as required.
#### •	pushButton
Responsible for communication from the Qt UI to the RTist part of the application. It uses an external port as the mechanism to allow the Qt main UI thread to inject an event when the user pushes the button in the Qt UI. Note that after each injected event the external port has to be enabled again to allow the button to be pushed another time.
The Qt UI needs access to the PushButton capsule so it can inject the event. In the sample this works by letting the PushButton state machine’s initial transition register the capsule instance with the MyThread. 
Note that the sample skips the start-up synchronization that typically is necessary for a real application. It may take some time for the RTist part of the application to start-up and during that time the Qt UI should not send messages to it. One typical solution would be to let the RTist application notify the Qt UI with a signal when it is ready to start accepting events.

### Project setup with the RTist and Qt Creator IDEs
Download the QTTrafficLight and TrafficLightsDemo zip files. Generate code from the RTist model in TrafficLightsDemo.zip using the TC “app_mingw”. Note that as it’s currently set-up RTist is only used for generating the code, and the build is fully done in the QT Creator IDE. In a more realistic set-up you would probably build a library from the RTist model and then let the Qt application link with it.
QTTrafficLight is a Qt project that should be built with Qt Creator. Note that this project includes source files generated from the RTist model. Refer to the .pro file of QTTrafficLight. Note that you may have to update the paths in the .pro file to match where you choose to place the RTist generated files.
For reference, the QTTrafficLight project was created using the following steps:
1.	Open QT Creator.
2.	Click on Create Project..
3.	Choose a template <Qt Widget Application> on New Project window. Click on <Choose>
4.	Give a project name e.g. QTtrafficLight and press on <next>
5.	Select build system <qmake> and press on <next>
6.	Uncheck <Generate form> on details page and press on <next>
7.	No change on <Translation> page and press on <next>
8.	On <kit> select <Desktop QT 6.7.0 MinGW 64-bit and press on <next>
9.	On Summary press on <finish>
10.	There are two static TargetRTS libs libObjecTime.a and libObjecTimeTypes.a present at following path in the RTist installation. 
\eclipse\rsa_rt\C++\TargetRTS\lib\WinT.x64-MinGw-12.2.0

There are two TargetRTS interfaces as mentioned below.
\eclipse\rsa_rt\C++\TargetRTS\include
\eclipse\rsa_rt\C++\TargetRTS\target\WinT

We have to add TargetRTS interface from these paths while adding TargetRTS libs. We have to add both libs one by one by selecting first path for first lib and second path for second lib.

Now right click on QTtrafficLight project and click on <Add Library…>. One popup window will appear. On popup windows select external library and press <Next>. 
Click on <Browse> and select library file, Click on second <Browse> and select TargetRTS interface. 

11.	Add windows socket lib in .pro file as below.
LIBS += -lwsock32
12.	Now right click on QTtrafficLight project and select <Add Existing Directory...> then select <Browse> for source code generated with RTist. Press <Start Parsing> and select only generated  .h/.cpp files.
13.	Add the path for generated .h/.cpp files in .pro file. (ws is workspace folder name used by me for eclipse).
INCLUDEPATH += $$PWD/../ws/TrafficLightsDemo_target

### Project deployment and using model debugging method
We have to deploy QTTrafficLight.exe executable with windeployqt.exe present in QT installation folder. I am using MinGW so path for windeployqt.exe will be at following location.
C:\QT\6.7.0\mingw_64\bin>windeployqt.exe
To run QTTrafficLight.exe from cmd, copy the exe created by QT IDE in separate folder. Let’s assume folder is created in C drive with name Executablefile.

Open the cmd and issue below command.

cd  C:\QT\6.7.0\mingw_64\bin

C:\QT\6.7.0\mingw_64\bin>windeployqt.exe C:\Executablefile\QTTrafficLight.exe

All supported files to run QTTrafficLight.exe from cmd will be created in Executablefile folder.

Now open a new cmd and run below command to run QTTrafficLight.exe and start model debugger from eclipse. 
C:\Executablefile>QTTrafficLight.exe -obslisten=12345

Refer the video present on following link for model debugging.

https://rtist.hcldoc.com/help/index.jsp?topic=%2Fcom.ibm.xtools.rsarte.webdoc%2FNewsletters%2FLaunching+debug+sessions+in+RTist.html&resultof%3D%2522%256d%256f%2564%2565%256c%2522%2520%2522%2564%2565%2562%2575%2567%2567%2569%256e%2567%2522%2520%2522%2564%2565%2562%2575%2567%2522%2520


