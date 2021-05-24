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
}

var (
	fileStateMap map[string]*FileState
)

func main() {
	fileStateMap = make(map[string]*FileState, 0)

	// git log --numstat > a.log
	file, err := os.Open("a.log")
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

	// 获取xml中的commit
	commitMp := getBugCommit()

	// 解析commit log
	for _, block := range loggers {
		commit := getLoggerCommit(block[0])
		if len(commit) == 0 {
			continue
		}
		if _, ok := commitMp[commit]; !ok {
			continue
		}
		for _, s := range block {
			parse(s)
		}
	}

	// 导出至 xlsx
	Export()
}
