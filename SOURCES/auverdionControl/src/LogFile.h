#ifndef LOGFILE_H
#define LOGFILE_H

#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QDateTime>

class CLogFile
{
public:
  CLogFile()
  {
    if( logfile )
    {
      logfile->close();
      delete logfile;
    }
    logfile = new QFile( "auverdionControl.log" );
    if( logfile->exists() )
      logfile->remove();
    if( logfile->open( QIODevice::ReadWrite ) )
    {
      ts.setDevice( logfile );
      ts<<"--- auverdionControl Log "<<QDateTime::currentDateTime().toString()<<" ---\n";
      ts.flush();
      #ifdef DEBUG
      qDebug()<<"--- auverdionControl Log "<<QDateTime::currentDateTime().toString()<<" ---\n";
      #endif
    }
  }

  ~CLogFile()
  {
    if( logfile )
    {
      logfile->close();
      delete logfile;
    }
  }

  inline CLogFile& operator<<( QString str )
  {
    ts<<str<<"\n";
    ts.flush();
    #ifdef DEBUG
    qDebug()<<str;
    #endif
    return *this;
  }

  inline CLogFile& operator<<( unsigned int val )
  {
    ts<<val<<"\n";
    ts.flush();
    #ifdef DEBUG
    qDebug()<<val;
    #endif
    return *this;
  }

  inline CLogFile& operator<<( int val )
  {
    ts<<val<<"\n";
    ts.flush();
    #ifdef DEBUG
    qDebug()<<val;
    #endif
    return *this;
  }

  inline CLogFile& operator<<( unsigned long long val )
  {
    ts<<val<<"\n";
    ts.flush();
    #ifdef DEBUG
    qDebug()<<val;
    #endif
    return *this;
  }

  inline CLogFile& operator()( void )
  {
    return *this;
  }

private:
  QTextStream ts;
  QFile* logfile;
};

#endif // CLOGFILE_H
