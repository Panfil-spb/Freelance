import openpyxl

def numbers(file_name):
    res_bas = openpyxl.Workbook()
    sheet_res_bas = res_bas.active
    count = 1
    bas = []

    book = openpyxl.open(f'{file_name}.xlsx')
    for sheet_name in book.get_sheet_names():
        sheet = book.get_sheet_by_name(sheet_name)
        for cellObj in sheet['A1':'Z150']:
            for cell in cellObj:
                try:
                    val = cell.value.split()
                    for number in val:
                        if "89" in number and len(number) == 11:
                            number = "".join(d for d in number if d.isdigit())
                            bas.append(number)
                except:
                    pass
        print(f"{sheet_name}-лист готов...")

    bas = list(set(bas))
    for i in range(len(bas)):
        sheet_res_bas.cell(i + 1, 1).value = bas[i]
    res_bas.save(f'{file_name}_base_numbers.xlsx')

def main():
    names = input("Введите названия файлов без расширения через пробел: ").split()
    for name in names:
        numbers(name)


main()