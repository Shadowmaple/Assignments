package main

import (
	"bufio"
	"log"
	"os"
	"strings"
)

type FileState struct {
	Name      string
	ChangeNum int   // 修改次数
	AddNum    int64 // 添加行数
	DeleteNum int64 // 删除行数
	Class     int   // 是否是bug修复文件
}

var (
	fileStateMap map[string]*FileState
)

func main() {
	fileStateMap = make(map[string]*FileState, 0)

	file, err := os.Open("rocketmq-4.7.0.log")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	loggers := make([][]string, 0)
	block := make([]string, 0)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineText := scanner.Text()
		if strings.Contains(lineText, "commit") {
			if len(block) > 0 {
				loggers = append(loggers, block)
				block = make([]string, 0)
			}
		}
		block = append(block, lineText)
	}

	// 获取当前版本的文件列表，作为需要统计的对象
	fileList := GetProFiles()
	for _, item := range fileList {
		fileStateMap[item] = &FileState{
			Name: item,
		}
	}

	// 解析日志文件块
	ParseLoggers(loggers)

	// 导出至 xlsx
	ExportCsv()
}
