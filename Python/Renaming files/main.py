import os.path
import shutil
import openpyxl


def read_file(file_name: str) -> list:
    work_book = openpyxl.load_workbook(file_name)

    sheet = work_book.active
    base = []
    for row in sheet.values:
        base.append(row)
    return base[1:]


def changes_files(list_names: list):
    count = 0
    len_list = len(list_names)
    for names in list_names:
        shutil.copy(names[0], names[1])
        count += 1
        print(f"Перемещено {count} из {len_list}")


def main():
    file_name = input("Введите название файла: ")
    if os.path.exists(file_name):
        print("ok")
    else:
        print("Такого файла не существует!\n")

    names_list = read_file(file_name)

    changes_files(names_list)


if __name__ == "__main__":
    main()
