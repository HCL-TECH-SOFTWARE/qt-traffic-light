# qt-traffic-light
This sample shows how a user interface implemented in Qt can be used for a realtime application developed with [DevOps Model RealTime](https://model-realtime.hcldoc.com/help/index.jsp) or [DevOps Code RealTime](https://secure-dev-ops.github.io/code-realtime/).

The sample is a variant of https://github.com/HCL-TECH-SOFTWARE/traffic-light-web which uses a web page as the user interface for a traffic light application. Here the web page has been replaced with a Qt UI based on the following sample from the Qt documentation:

https://doc.qt.io/qt-6/qtstatemachine-trafficlight-example.html

The state machine logic of this Qt sample was removed and replaced with the code generated from Model RealTime or Code RealTime.

### Building the sample
To build the sample you need to have Qt and a C++ toolchain installed. The sample is configured for Qt 6.7 on Windows, using the MinGw toolchain, but you can change this if you have another platform or toolchain. You also need to have either [Model RealTime](https://model-realtime.hcldoc.com/help/index.jsp) installed on Eclipse OR [Code RealTime](https://secure-dev-ops.github.io/code-realtime/) installed on Visual Studio Code or Eclipse Theia.

1. **Generate the realtime part of the application**
    
    a. If you want to use Model RealTime, open the [Model RealTime project](https://github.com/HCL-TECH-SOFTWARE/qt-traffic-light/tree/main/TrafficLightsDemo). Right-click on the TC `app_mingw.tcjs` and perform the command `Generate Code`.
    
    b. If you want to use Code RealTime, open the [Code RealTime workspace folder](https://github.com/secure-dev-ops/code-realtime/tree/main/art-samples/QtTrafficLight). Set the TC `app.tcjs` as active so that code gets generated for it.
2. **Set-up the Qt project**
   
   Open the Qt project [QTTrafficLight.pro](https://github.com/HCL-TECH-SOFTWARE/qt-traffic-light/tree/main/QTTrafficLight.pro) in a text editor. Set the `TARGET_RTS_LOCATION` variable to the location of the TargetRTS to use (located inside the Model RealTime or Code RealTime installations). Also set the `TARGET_FOLDER` variable to the location where generated code from Model RealTime or Code RealTime was placed.

3. **Build the application from Qt Creator**
   
   Open the Qt project [QTTrafficLight.pro](https://github.com/HCL-TECH-SOFTWARE/qt-traffic-light/tree/main/QTTrafficLight.pro) in Qt Creator and build it (using a command from the Build menu).	

### How the application works
We choose to let the main thread run the Qt UI. In `main.cpp` the QApplication is created with a main window. The main thread will then simply run the application’s event loop which handles all Qt UI events.

In the main window constructor (`MainWindow.cpp`) we create a QThread (`MyThread.cpp`) responsible for running the realtime part of the application. We use Qt signals and slots as the means of communicating messages from the realtime code to the Qt UI.

When the QThread starts to run (function `MyThread::run()`) it will call `RTMain::entryPoint()` and then pass necessary arguments which otherwise is provided by the TargetRTS. In the sample these are the path to the Qt application and “-URTS_DEBUG=quit” (to not use the model debugger). If you launch the Qt application with command-line arguments, these are passed to the TargetRTS. For example, to launch so that you can attach the model debugger to the application, use the `obslisten=<port>` argument.

The realtime part of the application is run by `MyThread` and uses a top capsule `TLSystem` with these capsule parts:
#### trafficLight
Implements the traffic light logic using a state machine. This part is independent of Qt.
#### pedLight
Implements the pedestrian light logic using a state machine. This part is independent of Qt.
#### qtUI
Responsible for communication from the realtime part of the application to the Qt UI. When events arrive from `trafficLight` or `pedLight`, the Qt application is notified by emitting the signals that were mapped in the `MainWindow` constructor. The mapped slot functions will then update the Qt UI as required.
#### pushButton
Responsible for communication from the Qt UI to the realtime part of the application. It uses an external port as the mechanism to allow the Qt main UI thread to inject an event when the user pushes the button in the Qt UI. Note that after each injected event the external port has to be enabled again to allow the button to be pushed another time.
The Qt UI needs access to the `PushButton` capsule so it can inject the event. In the sample this works by letting the `PushButton` state machine’s initial transition register the capsule instance with the `MyThread`. 

Note that the sample skips the start-up synchronization that typically is necessary for a real application. It may take some time for the realtime part of the application to start-up and during that time the Qt UI should not send messages to it. One typical solution would be to let the realtime part of the application notify the Qt UI with a signal when it is ready to start accepting events.

### How the Qt project was created
For reference, the QTTrafficLight project was created using the following steps:
1.	Open Qt Creator
2.	Create a new project (**File - New Project**)
3.	Choose the template `Qt Widgets Application` in the New Project dialog. Click the **Choose...** button.
4.	Give the project a name (QTtrafficLight) and set the file location and then press **Next**
5.	Select build system `qmake` and press **Next**
6.	Uncheck **Generate form** on the Details page and press **Next**
7.	Skip over the Translation page by pressing **Next**
8.	On the Kits page select `Desktop QT 6.7.0 MinGW 64-bit` and press **Next**
9.	On the Summary page press **Finish**
10.	There are two static TargetRTS libs `libObjecTime.a` and `libObjecTimeTypes.a` present in the Model/Code RealTime installation at this location: 

```
TargetRTS/lib/WinT.x64-MinGw-12.2.0
```

There are also two TargetRTS include folders:

```
TargetRTS/include
TargetRTS/target/WinT
```

We have to add the TargetRTS interfaces from these paths while adding TargetRTS libs. We have to add both libs one by one by selecting first path for first lib and second path for second lib.

Now right click on the QTTrafficLight project and select **Add Library…**. One popup window will appear. Select **External library** and press **Next**. 

Click the **Browse** buttons to locate the library file and include path (mentioned above). 

11.	Add Windows socket library by editing the QTTrafficLight.pro file in a text editor:

```
LIBS += -lwsock32
```

12.	Now right click on the QTTrafficLight project and select **Add Existing Directory...**. Click **Browse** to locate the source code generated by Model/Code RealTime. Press **Start Parsing** and select only the generated .h/.cpp files.
13.	Add the path for generated .h/.cpp files in .pro file.

```
INCLUDEPATH += $${TARGET_FOLDER}
```

Note that to make the Qt project work with both Model RealTime and Code RealTime the variables `TARGET_RTS_LOCATION` and `TARGET_FOLDER` were introduced and hard-coded paths were updated to use these variables instead.

### Project deployment and using the Model Debugger
To run the Qt application from the command-line we first have to deploy it using the `windeployqt.exe` utility. When using MinGw the path to this utility will be at a location similar to:

```
C:\QT\6.7.0\mingw_64\bin>windeployqt.exe
```

To run `QTTrafficLight.exe` from the command-line, copy the executable created by the Qt Creator IDE into a separate folder. Then run `windeployqt` with the path to the executable as argument. For example:

```
cd  C:\QT\6.7.0\mingw_64\bin

C:\QT\6.7.0\mingw_64\bin>windeployqt.exe C:\Executablefile\QTTrafficLight.exe
```

All files needed to run QTTrafficLight.exe from the command prompt will be created in the Executablefile folder.

Now we can start the Qt application with the flag that lets the Model Debugger attach to it:

```
C:\Executablefile>QTTrafficLight.exe -obslisten=12345
```

You may replace the port number with something that is available on your machine.

For more information about the Model Debugger, see [the documentation](https://model-realtime.hcldoc.com/help/topic/com.ibm.xtools.rsarte.webdoc/Articles/Running%20and%20debugging/index.html?cp=23_2_13).


