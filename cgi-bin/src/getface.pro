
LIBS += -L/opt/opencv4-pc/lib -lopencv_world\
-lSeetaFaceDetector \
-lSeetaFaceLandmarker \
-lSeetaFaceRecognizer \
-lSeetaFaceTracker \
-lSeetaNet \
-lSeetaQualityAssessor 


INCLUDEPATH += /opt/opencv4-pc/include/opencv4
INCLUDEPATH += /opt/opencv4-pc/include/opencv4/opencv2
INCLUDEPATH += /opt/opencv4-pc/include/opencv4
INCLUDEPATH += /opt/opencv4-pc/include/seeta
INCLUDEPATH += /opt/opencv4-pc/include/
INCLUDEPATH +=/usr/local/include
SOURCES += \
    main.cpp \
    sqlite3.c 
HEADERS += \
    sqlite3.h 
