#include "CFont.h"


namespace Sam3d
{

bool CFont::Load(char *name)
{
	Texture = Driver->LoadTextureFromFile(name);
	if (!Texture) 
		return false;//Текстура шрифта не найдена
	char* buff = (char*)Texture->lock();
	if ((Texture->getSize().Height!=256)&&(Texture->getSize().Width!=256))
		return false;//Неправильный размер текстуры
	//Создаем шрифт (определяем ширину символов)
	for (int y=0;y<16;y++)
		for (int x=0;x<16;x++)
		{
			if ((x+16*y)==32)
			{
				offset[x+y*16].left=0;
				offset[x+y*16].right=5;
				offset[x+y*16].top = y*16;
				offset[x+y*16].bottom = 16;
				continue;
			}

			int cx,cy;
			cy=y*16;
			cx=x*16-1;
			bool space=TRUE;
			while (space)
			{
				cx++;
				for (int t=0;t<16;t++)
					if (buff[(cx+(cy+t)*256)*4]>0)
					{
						space=false;
						break;
					}
					
			}
			offset[x+y*16].left= cx;
			offset[x+y*16].top = cy;
			cy=y*16;
			cx=(x+1)*16;
			space=TRUE;
			while (space)
			{
				cx--;
				for (int t=0;t<16;t++)
					if (buff[(cx+(cy+t)*256)*4]>0)
					{
						space=FALSE;
						break;
					}
				
			}
			offset[x+y*16].right = cx+1-offset[x+y*16].left;
			offset[x+y*16].bottom = 16;
		}
	//Конец цикла создания шрифта
		//Устанавливаем афльфа канал в текстуре шрифта
	for (int i=0;i<256*256;i++)
		buff[4*i + 3] = buff[4*i];
	
	Texture->unlock(); 
	return true;
};

void CFont::Draw(char* name, SColor color, Position2d<int> &position)
{
	if (!Texture) return; //Если текстуры нет то выходим
	unsigned char n;
	char* text = name;
	while (*text)
	{
		n = (*text);
		Position2d<int> clip;
		clip.x=offset[n].right;
		clip.y=16;
		Position2d<int> sPos;
		Position2d<int> clipPos;
		sPos.x = offset[n].left;
		sPos.y = offset[n].top;
		clipPos.x = offset[n].right;
		clipPos.y = 16;
		Driver->draw2DImage(position,clip,Texture,sPos,clipPos,color,true);
		position.x += offset[n].right;
		++text;
	}
};

bool CFont::loadTexture(ITexture *texture)
{
	return 0;
};

};