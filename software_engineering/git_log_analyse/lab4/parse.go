package main

import (
	"bufio"
	"log"
	"os"
	"regexp"
	"strconv"
)

var (
	rgx       = regexp.MustCompile(`(\d+)\t(\d+)\t(.+)`)
	commitRgx = regexp.MustCompile(`[Cc]ommit ([\da-z]{40})`)
)

func ParseLoggers(loggers [][]string) {
	// 获取xml中的commit
	// commitMp := getBugCommit()

	// 解析commit log
	for _, block := range loggers {
		// 当前commit是否是bug修复的commit，即这一系列文件的提交是否是因为bug修复的
		// commit := getLoggerCommit(block[0])
		// isBugCommit := 0
		// if len(commit) == 0 {
		// 	continue
		// }
		// if _, ok := commitMp[commit]; ok {
		// 	isBugCommit = 1
		// }
		// 解析文件名、增删行数
		for _, s := range block {
			parseLogFile(s)
		}
	}
}

// 正则解析git log文件字符串
func parseLogFile(line string) {
	matches := rgx.FindStringSubmatch(line)
	if len(matches) < 4 {
		return
	}

	fileName := matches[3]
	addNum, err := strconv.ParseInt(matches[1], 10, 32)
	if err != nil {
		return
	}
	deleteNum, err := strconv.ParseInt(matches[2], 10, 32)
	if err != nil {
		return
	}

	// 在此版本不存在该文件，可能已经被删除了，那么就不进行统计
	state, ok := fileStateMap[fileName]
	if !ok {
		return
	}

	state.ChangeNum++
	state.AddNum += addNum
	state.DeleteNum += deleteNum
	// if isBugCommit == 1 {
	// 	state.Class = "bug-prone"
	// } else {
	// 	state.Class = "not bug-prone"
	// }
}

// 解析 jira 日志文件
func getBugCommit() (res map[string]bool) {
	res = make(map[string]bool)
	file, err := os.Open("jira_rocketmq.xml")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineText := scanner.Text()
		matches := commitRgx.FindStringSubmatch(lineText)
		if len(matches) < 2 {
			continue
		}
		res[matches[1]] = true
	}

	return
}

// 解析获取 commit hash 值
func getLoggerCommit(line string) string {
	matches := commitRgx.FindStringSubmatch(line)
	if len(matches) < 2 {
		return ""
	}
	return matches[1]
}
