import os
from PIL import Image, ImageDraw #Подключим необходимые библиотеки.

def blackWhite(image, name):#функция отвечает за преобразования фото в ч/б версию
	draw = ImageDraw.Draw(image)  # Создаем инструмент для рисования.
	width = image.size[0]  # Определяем ширину.
	height = image.size[1]  # Определяем высоту.
	pix = image.load()  # Выгружаем значения пикселей.

	for i in range(width):#Учсредняем каждый пиксель
		for j in range(height):
			a = pix[i, j][0]
			b = pix[i, j][1]
			c = pix[i, j][2]
			S = (a + b + c) // 3
			draw.point((i, j), (S, S, S))

	image.save(name, "JPEG")#перезапись фото
	del draw#удаление кисти

def main():
	name_of_derr = input("Введите имя дерриктории для сканирования >>> ")
	tree = os.walk(name_of_derr)#берем переменную для хождения по деррикториям

	for addrees, dirs, files in tree:
		for file in files:
			name = addrees + '\\' + file#переход к следующей папке
			print("\n" + name, end='\t')

			if name[-1] != '.' and name != '..':#проверка на системные файлы
				if name[-3:] == "jpg":#проверка на формат файла
					try:
						image = Image.open(name)  # загрузка изоброжения
						blackWhite(image, name)
					except FileNotFoundError:
						print("Файл не найден")


main()