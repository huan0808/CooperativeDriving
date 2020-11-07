#include <iostream>
// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <string>
#include <cstdlib>

#include <signal.h>
/* shell command

pring all rs232 parameter
stty -F /dev/ttyLF1 -a  

set
stty -F /dev/ttyLF1 ispeed 115200 ospeed 115200 cs8 

print
cat /dev/ttyLF1

*/
using namespace std;

void signal_callback_handler(int signum); //异常处理
int serial_port;


int main()
{
  //打开串口
    serial_port = open("/dev/ttyACM0", O_RDWR| O_NOCTTY | O_SYNC);

  // 创建tty类
    termios tty;
  //防止异常退出
    signal(SIGINT, signal_callback_handler);
  // 获得现在的端口设置
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    tty.c_cflag &= ~PARENB; /* no parity */
    tty.c_cflag &= ~CSTOPB; /* 1 stop bit */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8 | CLOCAL; /* 8 bits */
    /* echo off, echo newline off, canonical mode off,
     * extended input processing off, signal chars off
     */
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    tty.c_oflag = 0; /* Turn off output processing */
    tty.c_cflag &=  ~CRTSCTS;
    /* Read settings :
     * To understand the settings have a look at man 3 termios
     * ``Canonical and noncanonical mode`` section
     */
    tty.c_cc[VMIN]   =  1; /* read doesn't block */
    tty.c_cc[VTIME]  =  1; /* read timeout in ds */
    tty.c_cflag     |=  CREAD;

    /* Flush Port, then applies attributes */
    tcflush(serial_port, TCIFLUSH);
    if (tcsetattr(serial_port, TCSANOW, &tty) < 0) /* apply the settings */
        return -1;

    // Set in/out baud rate 
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    // Write to serial port
    /*
    string str = "$cmd";
    write(serial_port, str.c_str(), sizeof(str.c_str()));
    */
    char buffer[1024];
    memset(buffer,0, sizeof(buffer));
    int n = read(serial_port, &buffer, sizeof(buffer));
    if ( n < 0) {
        perror("read");
        return 1;
    }
    for(int i = 0; i < 1024; i++)
    {
        cout << buffer[i] << endl;
    }
    
    close(serial_port);
    return 0; // success
}
/*


  while(true)
  {
      // Allocate memory for read buffer, set size according to your needs
        char buffer[1024];
        memset(buffer,0, sizeof(buffer));
        int n = read(serial_port, &buffer, sizeof(buffer));
        string str;
        string FPD_Header;
        string FPD_GPSWeek;
        string FPD_GPSTime;
        string Heading;
        string Pitch;
        string Roll;
        string Lattitude;
        string Longitude;
        string Altitude;
        string Ve;
        string Vn;
        string Vu;
        string Baseline;
        string NSV1;
        string NSV2;
        string Status;
        string FPD_Cs;
        string FPD_CrLf;
        int num = 0;
        int flag = 0;
        if(n>0)
        {
           
            if(FPD_Data_Check(buffer,n)==0)//如果校验不通过则跳过
            {
                continue;
            }
            for(int i=0; i<n; i++)
            {
                if(buffer[i]==',')
                {
                    num++; 
                }
                else if(i != 0 && buffer[i] == '>' && buffer[i - 1] == 'F' )
                {
                    break;
                }
                else 
                {
                    if(num==0)
                    {
                        FPD_Header+=buffer[i];   
                    }
                    else if(num==1)
                    {
                        FPD_GPSWeek+=buffer[i];
                    }
                    else if(num==2)
                    {
                        FPD_GPSTime+=buffer[i];
                    }
                    else if(num==3)
                    {
                        Heading+=buffer[i];
                    }
                    else if(num==4)
                    {
                        Pitch+=buffer[i];
                    }
                    else if(num==5)
                    {
                        Roll+=buffer[i];
                    }
                    else if(num==6)
                    {
                        Lattitude+=buffer[i];
                    }
                    else if(num==7)
                    {
                        Longitude+=buffer[i];
                    }
                    else if(num==8)
                    {
                        Altitude+=buffer[i];
                    #include <iostream>
// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <string>
/* shell command

pring all rs232 parameter
stty -F /dev/ttyLF1 -a  

set
stty -F /dev/ttyLF1 ispeed 115200 ospeed 115200 cs8 

print
cat /dev/ttyLF1
}
                    else if(num==9)
                    {
                        Ve+=buffer[i];
                    }
                    else if(num==10)
                    {
                        Vn+=buffer[i];
                    }
                    else if(num==11)
                    {
                        Vu+=buffer[i];
                    }
                    else if(num==12)
                    {
                        Baseline+=buffer[i];
                    }
                    else if(num==13)
                    {
                        NSV1+=buffer[i];
                    }
                    else if(num==14)
                    {
                        NSV2 += buffer[i];
                    }
                    else if(num == 15)
                    {
                        if(flag<2)
                        {
                            Status += buffer[i];
                        }
                        else if(flag>=2&&flag<5)
                        {
                            FPD_Cs+=buffer[i];
                        }
                        else if(flag>=5)
                        {
                            FPD_CrLf+=buffer[i];
                        }
                        flag++;
                    }
                } 
            }              
  }
*/


  // Normally you wouldn't do this memset() call, but since we will just receive
  // ASCII data for this example, we'll set everything to 0 so we can
  // call printf() easily.


  // Read bytes. The behaviour of read() (e.g. does it block?,
  // how long does it block for?) depends on the configuration
  // settings above, specifically VMIN and VTIME

  // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
  /*
  if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
  }
  */

  // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
  // print it to the screen like this!)
  //printf("Read %i bytes. Received message: %s", num_bytes, read_buf);



void signal_callback_handler(int signum) {
   cout << "Caught signal " << signum << endl;
   close(serial_port);
   // Terminate program
   exit(signum);
}