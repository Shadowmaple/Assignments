package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

type FileState struct {
	Name      string
	ChangeNum int   // 修改次数
	AddNum    int64 // 添加行数
	DeleteNum int64 // 删除行数
}

var (
	fileStateMap map[string]*FileState
	logFile      *os.File
)

// 导出结果至 excel
func print() {
	for key, value := range fileStateMap {
		fmt.Println(key, value.ChangeNum, value.AddNum, value.DeleteNum)
		// fmt.Fprintln(logFile, key, value.ChangeNum, value.AddNum, value.DeleteNum)
	}
}

func main() {
	fileStateMap = make(map[string]*FileState, 0)

	// git log --numstat rocketmq-all-4.7.0 > rocketmq-4.7.0.log
	file, err := os.Open("rocketmq-4.7.0.log")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// 打开运行日志文件，记录可能存在的错误信息，以便于排查
	logFile, err = os.OpenFile("data.log", os.O_RDWR|os.O_APPEND|os.O_CREATE, 0666)
	if err != nil {
		log.Fatal(err)
	}
	defer logFile.Close()

	loggers := make([][]string, 0)
	block := make([]string, 0)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineText := scanner.Text()
		if strings.Contains(lineText, "commit") {
			loggers = append(loggers, block)
			block = make([]string, 0)
		} else {
			block = append(block, lineText)
		}
	}

	// 获取当前版本的文件列表，作为需要统计的对象
	fileList := GetProFiles()
	for _, item := range fileList {
		fileStateMap[item] = &FileState{
			Name: item,
		}
	}

	// 解析commit log
	for _, block := range loggers {
		// fmt.Fprintln(logFile, "-------------------")
		for _, s := range block {
			parse(s)
			// fmt.Fprintln(logFile, s)
		}
	}

	// 导出至 xlsx
	Export()
}
