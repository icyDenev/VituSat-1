#include <bits/stdc++.h>
#include <thread>
//#include <boost>
//#include "gnuplot-iostream/gnuplot-iostream.h"

using namespace std;

void replacefile(string sauce, int length)
{
    const char * c = sauce.c_str();
    string s;
    ofstream temp;
    temp.open("temp.txt");
    ifstream input;
    input.open(c);
    getline(input, s);
    for(int i=0; i<length; i++)
    {
        input>>s;
        temp<<s<<" "<<i<<"\n";
        getline(input, s);
    }
    temp.close();
    input.close();
    remove(c);
    int result = rename("temp.txt", c);
    /*if ( result == 0 )
    puts ( "File successfully renamed" );
  else
    perror( "Error renaming file" );*/

    return;
}

int main()
{
    string s;
    int seconds=1;
    ifstream logfile;
    fstream gps, temp, press, accelX, accelY, accelZ, velo;
    logfile.open("data.txt");
    while(logfile.is_open())
    {
        if(seconds==30)
        {
            s = "gps.log";
            replacefile(s, seconds);
            s = "accelX.log";
            replacefile(s, seconds);
            s = "accelY.log";
            replacefile(s, seconds);
            s = "accelZ.log";
            replacefile(s, seconds);
            s = "temp.log";
            replacefile(s, seconds);
            s = "press.log";
            replacefile(s, seconds);
            s = "velo.log";
            replacefile(s, seconds);
            seconds--;
        }
        gps.open("gps.log", ios::app);
        press.open("press.log", ios::app);
        temp.open("temp.log", ios::app);
        accelZ.open("accelX.log", ios::app);
        accelY.open("accelY.log", ios::app);
        accelZ.open("accelZ.log", ios::app);
        velo.open("velo.log", ios::app);

        //system ("type com5: >> data.log");
        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        gps<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        accelX<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        accelY<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        accelZ<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        press<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        temp<<s<<" "<<seconds<<"\n";

        logfile>>s;
        if(s=="Transceiver")logfile>>s>>s;
        velo<<s<<" "<<seconds<<"\n";

        gps.close();
        accelX.close();
        accelY.close();
        accelZ.close();
        temp.close();
        press.close();
        velo.close();
        //system ("liveplot.gnu");
        this_thread::sleep_for(1000ms);
        seconds++;
    }
    logfile.close();
    temp.close();
    //s="data.log";
    //replacefile(s, 29);
    //system("echo plot sin(x) | C:\\Progra~1\\gnuplot\\bin\\gnuplot.exe");
    //this_thread::sleep_for(10000ms);
    return 0;
}
