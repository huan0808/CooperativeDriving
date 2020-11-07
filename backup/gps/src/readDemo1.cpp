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
void signal_callback_handler(int signum); //异常处理
int serial_port;

using namespace std;


int main()
{
  //打开串口
    serial_port = open("/dev/ttyACM0", O_RDWR);

  // 创建tty类
    termios tty;
  //防止异常退出
    signal(SIGINT, signal_callback_handler);
  // 获得现在的端口设置
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    tty.c_cflag &= ~PARENB; // 不设置奇偶效验
    tty.c_cflag &= ~CSTOPB; // 停止位为1位
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
    tty.c_cflag |= CS8; // 8 bits per byte (most common)设置
    tty.c_cflag &= ~CRTSCTS; 
    tty.c_cflag |= CREAD | CLOCAL; 

    tty.c_lflag &= ~ICANON; //canonical模式下是一行一行接收的，将其禁用会收到原始数据

    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // 关闭软硬件控制流
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // 禁用所有特殊字符的处理

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 1;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

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