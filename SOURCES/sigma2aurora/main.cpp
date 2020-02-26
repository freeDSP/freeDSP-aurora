#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("sigma2aurora");
  QCoreApplication::setApplicationVersion("0.0.1");

  QCommandLineParser parser;
  parser.setApplicationDescription( "Converts SigmaStudio export files to Aurora DSp files." );
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument( "numbytes", QCoreApplication::translate( "main", "NumBytes_*.dat file of SigmaStudio export." ) );
  parser.addPositionalArgument( "txbuffer", QCoreApplication::translate( "main", "TxBuffer_*.dat file of SigmaStudio export." ) );

  parser.process( app );

  const QStringList args = parser.positionalArguments();

  if( args.size() != 2 )
  {
    parser.showHelp();
    exit( EXIT_FAILURE );
  }

  QString pathNumBytes = args.at(0);
  QString pathTxBuffer = args.at(1);

  qDebug()<<pathNumBytes;
  qDebug()<<pathTxBuffer;

  QFile fileTxBuffer( pathTxBuffer );
  QFile fileNumBytes( pathNumBytes );
  if( !fileTxBuffer.exists() )
  {
    std::cout<<"File"<<pathTxBuffer.toStdString()<<"does not exist"<<std::endl;
    exit( EXIT_FAILURE );
  }
  if( !fileNumBytes.exists() )
  {
    std::cout<<"File"<<pathNumBytes.toStdString()<<"does not exist"<<std::endl;
    exit( EXIT_FAILURE );
  }

  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    std::cout<<__FILE__<<__LINE__<<"Could not open selected file"<<pathTxBuffer.toStdString()<<std::endl;
    exit( EXIT_FAILURE );
  }

  QTextStream in( &fileTxBuffer );
  QStringList listTxBuffer;

  while( !in.atEnd() )
  {
    QString line = in.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( str.startsWith( "0x" ) )
        listTxBuffer<<str;
    }
  }

  fileTxBuffer.close();

  //----------------------------------------------------------------------------
  //--- Read and convert the NumBytes_IC_1.dat file
  //----------------------------------------------------------------------------
  if( !fileNumBytes.open( QIODevice::ReadOnly ) )
  {
    std::cout<<__FILE__<<__LINE__<<"Could not open selected file"<<pathNumBytes.toStdString()<<std::endl;
    exit( EXIT_FAILURE );
  }

  QTextStream indat( &fileNumBytes );
  QStringList listNumBytes;

  while( !indat.atEnd() )
  {
    QString line = indat.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( !str.isEmpty() )
        listNumBytes<<str;
    }
  }

  fileNumBytes.close();

  //----------------------------------------------------------------------------
  //--- Compose the data file content
  //----------------------------------------------------------------------------
  QByteArray content;
  int32_t offset = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
  {
    uint32_t numbytes = listNumBytes[ii].toUInt( nullptr, 10 );

    content.append( static_cast<char>((numbytes >> 24) & 0xFF) );
    content.append( static_cast<char>((numbytes >> 16) & 0xFF) );
    content.append( static_cast<char>((numbytes >>  8) & 0xFF) );
    content.append( static_cast<char>(        numbytes & 0xFF) );

    for( uint32_t n = 0; n < numbytes; n++ )
    {
      if( offset >= listTxBuffer.size() )
      {
        std::cout<<"TxBuffer too small"<<std::endl;
        exit( EXIT_FAILURE );
      }

      char data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      content.append( data );
      offset++;
    }
  }

  //----------------------------------------------------------------------------
  //--- Write firmware file
  //----------------------------------------------------------------------------
  QFile file( "dsp.fw" );
  if( !file.open( QIODevice::WriteOnly ) )
  {
    std::cout<<"Could not open dsp.fw for writing"<<std::endl;
    exit( EXIT_FAILURE );
  }

  if( file.write( content ) == -1 )
  {
    std::cout<<"Failed writing to dsp.fw"<<std::endl;
    exit( EXIT_FAILURE );
  }

  file.close();

  return 0; //app.exec();
}
