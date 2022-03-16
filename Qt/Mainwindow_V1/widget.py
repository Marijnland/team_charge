# This Python file uses the following encoding: utf-8
import sys
from PySide6 import QtCore
from PySide6.QtWidgets import QApplication, QMainWindow
from ui_mainwindow import Ui_MainWindow
import datetime


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.seee.clicked.connect(self.isclicked)

    @QtCore.Slot()
    def isclicked(self):
        Time = datetime.datetime.now()
        self.ui.time.setText('Time: %s:%s' % (Time.hour, Time.minute))


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()
    sys.exit(app.exec())

    # For fullscreen (end product) :
    # window.showFullScreen()
    # uic mainwindow.ui > ui_mainwindow.py -g python
