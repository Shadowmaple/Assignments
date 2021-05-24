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

// 正则解析字符串
func parse(line string) {
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

func getLoggerCommit(line string) string {
	matches := commitRgx.FindStringSubmatch(line)
	if len(matches) < 2 {
		return ""
	}
	return matches[1]
}
