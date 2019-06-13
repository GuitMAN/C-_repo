#ifndef __Screamer
#define __Screamer
//#include <windows.h>
#include <time.h>
#include <StdIo.H>
#include <StdLib.H>
#include <StdArg.H>
#include <String.H>
#include <fstream>

#define OutputFile      "Log.html"                                      
#define Log     Message()                                                               


class Screamer 
{
private:
	std::fstream LogFile;                                                                
        char *HTML;
        char *PrevHTML;

        Screamer()                                                                              
        {
			LogFile.open(OutputFile,std::ios::out);
			LogFile.close();

			HTML = (char*) calloc(256,sizeof(char));
			PrevHTML = (char*) calloc(256,sizeof(char));

			WriteCode("<Title>Log File</Title>");
			WriteCode("<Html> <Body BgColor = Cornsilk>");
			WriteCode("<B><Font Size = 3 Color = DarkBlue Face = Verdana>Файл лога </B><BR>");
        }

public:
        ~Screamer()
        {
			WriteCode("</Font> </P> </Body> </Html>");
			free (PrevHTML);
			free (HTML);
        }
        
        void Write(const char* Color, const char *String, ...);
        void WriteBold(const char* Color, const char *String, ...);
        void WriteCode(const char *String);
        void WriteLine(); 
        friend Screamer& Message();                                             
};



inline void Screamer::Write(const char* Color, const char *String, ...)
{
        if (!String) return;
        
        char LogText[1024];
        
        va_list Print;                                                                  

        va_start(Print, String);
        vsprintf(LogText, String, Print);                   
        va_end(Print);
        
		LogFile.open(OutputFile,std::ios::app);

        strcat(HTML,"<Font Size = 2 Color = ");                 
        strcat(HTML,Color);                                                             
        strcat(HTML," Face = Verdana>");                                


		// Добавляем текущую дату и время
		time_t ltime;
		time(&ltime);
		char *mtime=ctime(&ltime);
		mtime[strlen(mtime)-1]=0;

		if (strcmp(PrevHTML,HTML)!=0)                                   
        {
                strcpy(PrevHTML,HTML);                                          
				LogFile<<"</Font>"<<std::endl;                                       
				LogFile<<HTML<<std::endl;                                            
                *HTML=NULL;                                                                     
        }


//		////MainConsole->Add(0,LogText);<<" : "
		LogFile<<"<BR>"<<LogText<<std::endl;  
        LogFile.close();
}

inline void Screamer::WriteBold(const char* Color, const char *String, ...)
{
        if (!String) return;
        
        char LogText[1024];
        
        va_list Print;                                                          

        va_start(Print, String);
        vsprintf(LogText, String, Print);           
        va_end(Print);
        
        WriteCode("<B>");
        Write(Color,String);
        WriteCode("</B>");
}

inline void Screamer::WriteCode(const char *String)
{
	LogFile.open(OutputFile,std::ios::app);
	LogFile<<String<<std::endl;
        LogFile.close();
}

inline void Screamer::WriteLine()
{
	WriteCode("<HR>");
}

inline Screamer& Message()
{
        static Screamer SingleObject;                           
        return SingleObject;
}


#endif

