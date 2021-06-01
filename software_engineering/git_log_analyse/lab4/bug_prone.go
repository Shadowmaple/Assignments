package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

// 获取指定版本后的文件是否是bug修复的
func getVersionLogFiles() (res map[string]bool) {
	res = make(map[string]bool)

	file, err := os.Open("rocketmq-4.7.0-after.log")
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
	// commitMp := getBugCommit()

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

		for _, line := range block {
			matches := rgx.FindStringSubmatch(line)
			if len(matches) < 4 {
				continue
			}
			fileName := matches[3]
			res[fileName] = true
			// if isBugCommit == 1 {
			// 	res[fileName] = true
			// } else {
			// 	res[fileName] = false
			// }
		}
	}

	for k, _ := range res {
		fmt.Println(k)
	}

	return
}

func SetBugProne() {
	mp := getVersionLogFiles()
	for k, state := range fileStateMap {
		isBug, ok := mp[k]
		if !ok {
			continue
		}
		if isBug {
			state.Class = "bug-prone"
		} else {
			state.Class = "not bug-prone"
		}
	}
}
