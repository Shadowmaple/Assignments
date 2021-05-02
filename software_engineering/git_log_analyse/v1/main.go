package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type FileState struct {
	Name      string
	ChangeNum int   // 修改次数
	AddNum    int64 // 添加行数
	DeleteNum int64 // 删除行数
}

var (
	rgx          = regexp.MustCompile("(\\d+)\\t(\\d+)\\t(.+)")
	fileStateMap map[string]*FileState
	logFile      *os.File
)

// 正则解析字符串
func parse(line string) {
	matches := rgx.FindStringSubmatch(line)
	if len(matches) < 4 {
		// fmt.Fprintln(logFile, line, len(matches), matches)
		return
	}

	fmt.Println(matches)

	fileName := matches[3]
	addNum, err := strconv.ParseInt(matches[1], 10, 32)
	if err != nil {
		fmt.Fprintln(logFile, err.Error())
		return
	}
	deleteNum, err := strconv.ParseInt(matches[2], 10, 32)
	if err != nil {
		fmt.Fprintln(logFile, err.Error())
		return
	}

	state, ok := fileStateMap[fileName]
	if !ok {
		state = &FileState{
			Name:      fileName,
			ChangeNum: 1,
			AddNum:    addNum,
			DeleteNum: deleteNum,
		}
		fileStateMap[fileName] = state
	} else {
		state.ChangeNum++
		state.AddNum += addNum
		state.DeleteNum += deleteNum
	}
}

// 导出结果至 excel
func print() {
	for key, value := range fileStateMap {
		fmt.Println(key, value.ChangeNum, value.AddNum, value.DeleteNum)
		// fmt.Fprintln(logFile, key, value.ChangeNum, value.AddNum, value.DeleteNum)
	}
}

func main() {
	fileStateMap = make(map[string]*FileState, 0)

	file, err := os.Open("a.log")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

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

	for _, block := range loggers {
		// fmt.Fprintln(logFile, "-------------------")
		for _, s := range block {
			parse(s)
			// fmt.Fprintln(logFile, s)
		}
	}

	// print()
	Export()
}
