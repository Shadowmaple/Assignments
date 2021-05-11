package main

import (
	"fmt"
	"strconv"

	"github.com/360EntSecGroup-Skylar/excelize"
)

// 导出至 excel 文件
func Export() {
	f := excelize.NewFile()
	// Create a new sheet.
	sheetName := "sheet1"
	index := f.NewSheet(sheetName)
	// Set active sheet of the workbook.
	f.SetActiveSheet(index)

	// 设置首行
	category := map[string]string{
		"A1": "fileName", "B1": "changeRate", "C1": "addNum", "D1": "deleteNum",
	}
	for k, v := range category {
		f.SetCellValue(sheetName, k, v)
	}

	// 写入
	row := 2
	for key, value := range fileStateMap {
		rowStr := strconv.Itoa(row)
		f.SetCellValue(sheetName, "A"+rowStr, key)
		f.SetCellValue(sheetName, "B"+rowStr, value.ChangeNum)
		f.SetCellValue(sheetName, "C"+rowStr, value.AddNum)
		f.SetCellValue(sheetName, "D"+rowStr, value.DeleteNum)
		row++
	}

	// Save spreadsheet by the given path.
	if err := f.SaveAs("result.xlsx"); err != nil {
		fmt.Println(err)
	}
}
