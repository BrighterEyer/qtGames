#include<QApplication>
#include"look.h"
//#include<unistd.h>
int main(int argc, char** argv){
    QApplication qa(argc, argv);
    Look look;
    look.show ();
    look.resize (450, 390);
    // look.buttonRemove ();
    return qa.exec ();
}
