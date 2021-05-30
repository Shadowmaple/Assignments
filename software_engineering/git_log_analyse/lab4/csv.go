package main

import (
	"encoding/csv"
	"os"
	"strconv"
)

func ExportCsv() {
	f, err := os.Create("result.csv") //创建文件
	if err != nil {
		panic(err)
	}
	defer f.Close()

	f.WriteString("\xEF\xBB\xBF") // 写入UTF-8 BOM

	w := csv.NewWriter(f) //创建一个新的写入文件流
	data := [][]string{
		{"fileName", "changeRate", "addNum", "deleteNum", "class"},
	}

	for key, value := range fileStateMap {
		data = append(data, []string{
			key,
			strconv.Itoa(value.ChangeNum),
			strconv.Itoa(int(value.AddNum)),
			strconv.Itoa(int(value.DeleteNum)),
			strconv.Itoa(value.Class),
		})
	}

	w.WriteAll(data) //写入数据
	w.Flush()
}
