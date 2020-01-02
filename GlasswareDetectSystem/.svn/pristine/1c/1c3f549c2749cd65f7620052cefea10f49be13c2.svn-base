#include "stateTool.h"
#include <QTextStream>

bool StateTool::writeInit(QString path, QString user_key, QString user_value)
{
	if(path.isEmpty() || user_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);

		//将信息写入配置文件
		config->beginGroup("config");
		config->setValue(user_key, user_value);
		config->endGroup();

		return true;
	} 
}

bool StateTool::readInit(QString path, QString user_key, QString &user_value)
{
	user_value = QString("");
	if(path.isEmpty() || user_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);

		//读取用户配置信息
		user_value = config->value(QString("config/") + user_key).toString();

		return true;
	}  
}

bool StateTool::updateText(QString text, int max_width, QString &elided_text)
{
	elided_text = QString("");
	if(text.isEmpty() || max_width <= 0)
	{
		return false;
	}

	QFont ft;
	QFontMetrics fm(ft);
	elided_text = fm.elidedText(text, Qt::ElideRight, max_width);

	return true;
}

QString StateTool::getSkinName()
{
	QString skin_name = DEFAULT_SKIN;
//	bool is_read = StateTool::readInit(QString("./user.ini"), QString("skin"), skin_name);

	return skin_name;
}

bool StateTool::WritePrivateProfileQString(QString strSectionName, QString strKeyName, QString strValue, QString strFileName)
{
	bool ret = false;

	//section是null则直接返回false
	if(strSectionName.isEmpty())
	{
		return ret;
	}

	bool flagFindSection = false;//是否找到了section
	int pos = 0;
	QString strSection("[" + strSectionName + "]");
	QString strKey(strKeyName + "  =");
	QString strKey1(strKeyName + "=");
	QString strKey2(strKeyName + " =");

	//文件不存在，则创建，且直接写入
	if(!QFile::exists(strFileName))
	{
		QFile createFile(strFileName);
		if(!createFile.open(QFile::WriteOnly | QIODevice::Text))
		{
			return ret;
		}
		//如果key和value不是null，才写内容
		if(!strKeyName.isEmpty() && !strValue.isEmpty())
		{
			QTextStream createStream(&createFile);
			createStream<<strSection<<"\n";
			createStream<<strKey<<strValue<<"\n";
			createStream.flush();

			ret = true;
		}
		createFile.close();
		return ret;
	}

	QFile readFile(strFileName);

	if (!readFile.open(QFile::ReadOnly | QIODevice::Text))
	{
		ret = false;
		return ret;
	}

	QFile writeFile(strFileName);

	//读入流和写入流
	//写入流文件在最后才WriteOnly打开
	QTextStream readStream(&readFile);
	QTextStream writeStream(&writeFile);

	//查找每一行是否包含section
	while (!readStream.atEnd())
	{
		QString line(readStream.readLine());

		if (line.indexOf(strSection) != 0) //该行不包含section，直接写入流
		{
			writeStream<<line<<"\n";
		}
		else  
		{
			flagFindSection = true; //查到section
			ret = true;

			//key是null，则跳过该section,写入其余section
			if (strKeyName.isEmpty())
			{
				do //跳过该section
				{
					line = QString(readStream.readLine());
				} while (line.indexOf("[") != 0 && !readStream.atEnd());

				if(readStream.atEnd())
				{
					break;
				}
				else //写入其余section
				{
					writeStream<<line<<"\n";
					while(!readStream.atEnd())
					{
						writeStream<<readStream.readLine()<<"\n";
					}
					break;
				}
			}

			writeStream<<line<<"\n";//section写入流
			line = QString(readStream.readLine());
			while(line.indexOf(strKey) != 0 && line.indexOf(strKey1) != 0 && line.indexOf(strKey2) != 0 && line.indexOf("[") != 0 && !readStream.atEnd())
			{
				writeStream<<line<<"\n";
				line = QString(readStream.readLine());
			}

			if(line.indexOf(strKeyName) == 0)//查到key，若value!=null则修改value
			{
				if(!strValue.isEmpty())
				{
					line = line.mid(0, line.indexOf("=") + 1) + strValue;
					writeStream<<line<<"\n";
				}
				while(!readStream.atEnd()) //剩余行写入流中
				{
					writeStream<<readStream.readLine()<<"\n";
				}
				break;
			}
			else if(line.indexOf("[") == 0)//查到下一个section，若value!=null则在下一个section前直接加上key
			{
				if(!strValue.isEmpty())
				{
					writeStream<<strKey<<strValue<<"\n";
				}
				writeStream<<line<<"\n";
				while(!readStream.atEnd()) //剩余行写入流中
				{
					writeStream<<readStream.readLine()<<"\n";
				}
				break;
			}
			else if(readStream.atEnd())//文件末尾，若value!=null则直接加上key
			{
				//直接加上
				if(!strValue.isEmpty())
				{

					writeStream<<line<<"\n"<<strKey<<strValue<<"\n";
				}
			}

		}
	}
	if(!flagFindSection)//若未查到该section，且key和value！=null，写入section和key=value
	{
		if(!strKeyName.isEmpty() && !strValue.isEmpty())
		{
			writeStream<<strSection<<"\n";
			writeStream<<strKey<<strValue<<"\n";
		}
	}
	readFile.close();

	//写打开文件
	if (!writeFile.open(QFile::WriteOnly | QIODevice::Text))
	{
		ret = false;
		return ret;
	}
	writeStream.flush();//写入流到文件

	writeFile.close();

	return ret;
}
