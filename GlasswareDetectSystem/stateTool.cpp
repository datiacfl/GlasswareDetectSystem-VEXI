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
		//���������ļ���������
		QSettings *config = new QSettings(path, QSettings::IniFormat);

		//����Ϣд�������ļ�
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
		//���������ļ���������
		QSettings *config = new QSettings(path, QSettings::IniFormat);

		//��ȡ�û�������Ϣ
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

	//section��null��ֱ�ӷ���false
	if(strSectionName.isEmpty())
	{
		return ret;
	}

	bool flagFindSection = false;//�Ƿ��ҵ���section
	int pos = 0;
	QString strSection("[" + strSectionName + "]");
	QString strKey(strKeyName + "  =");
	QString strKey1(strKeyName + "=");
	QString strKey2(strKeyName + " =");

	//�ļ������ڣ��򴴽�����ֱ��д��
	if(!QFile::exists(strFileName))
	{
		QFile createFile(strFileName);
		if(!createFile.open(QFile::WriteOnly | QIODevice::Text))
		{
			return ret;
		}
		//���key��value����null����д����
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

	//��������д����
	//д�����ļ�������WriteOnly��
	QTextStream readStream(&readFile);
	QTextStream writeStream(&writeFile);

	//����ÿһ���Ƿ����section
	while (!readStream.atEnd())
	{
		QString line(readStream.readLine());

		if (line.indexOf(strSection) != 0) //���в�����section��ֱ��д����
		{
			writeStream<<line<<"\n";
		}
		else  
		{
			flagFindSection = true; //�鵽section
			ret = true;

			//key��null����������section,д������section
			if (strKeyName.isEmpty())
			{
				do //������section
				{
					line = QString(readStream.readLine());
				} while (line.indexOf("[") != 0 && !readStream.atEnd());

				if(readStream.atEnd())
				{
					break;
				}
				else //д������section
				{
					writeStream<<line<<"\n";
					while(!readStream.atEnd())
					{
						writeStream<<readStream.readLine()<<"\n";
					}
					break;
				}
			}

			writeStream<<line<<"\n";//sectionд����
			line = QString(readStream.readLine());
			while(line.indexOf(strKey) != 0 && line.indexOf(strKey1) != 0 && line.indexOf(strKey2) != 0 && line.indexOf("[") != 0 && !readStream.atEnd())
			{
				writeStream<<line<<"\n";
				line = QString(readStream.readLine());
			}

			if(line.indexOf(strKeyName) == 0)//�鵽key����value!=null���޸�value
			{
				if(!strValue.isEmpty())
				{
					line = line.mid(0, line.indexOf("=") + 1) + strValue;
					writeStream<<line<<"\n";
				}
				while(!readStream.atEnd()) //ʣ����д������
				{
					writeStream<<readStream.readLine()<<"\n";
				}
				break;
			}
			else if(line.indexOf("[") == 0)//�鵽��һ��section����value!=null������һ��sectionǰֱ�Ӽ���key
			{
				if(!strValue.isEmpty())
				{
					writeStream<<strKey<<strValue<<"\n";
				}
				writeStream<<line<<"\n";
				while(!readStream.atEnd()) //ʣ����д������
				{
					writeStream<<readStream.readLine()<<"\n";
				}
				break;
			}
			else if(readStream.atEnd())//�ļ�ĩβ����value!=null��ֱ�Ӽ���key
			{
				//ֱ�Ӽ���
				if(!strValue.isEmpty())
				{

					writeStream<<line<<"\n"<<strKey<<strValue<<"\n";
				}
			}

		}
	}
	if(!flagFindSection)//��δ�鵽��section����key��value��=null��д��section��key=value
	{
		if(!strKeyName.isEmpty() && !strValue.isEmpty())
		{
			writeStream<<strSection<<"\n";
			writeStream<<strKey<<strValue<<"\n";
		}
	}
	readFile.close();

	//д���ļ�
	if (!writeFile.open(QFile::WriteOnly | QIODevice::Text))
	{
		ret = false;
		return ret;
	}
	writeStream.flush();//д�������ļ�

	writeFile.close();

	return ret;
}
