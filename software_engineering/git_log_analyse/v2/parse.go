package main

import (
	"fmt"
	"regexp"
	"strconv"
)

var rgx = regexp.MustCompile("(\\d+)\\t(\\d+)\\t(.+)")

// 正则解析字符串
func parse(line string) {
	matches := rgx.FindStringSubmatch(line)
	if len(matches) < 4 {
		// fmt.Fprintln(logFile, line, len(matches), matches)
		return
	}

	// fmt.Println(matches)

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

	// 在此版本不存在该文件，可能已经被删除了，那么就不进行统计
	state, ok := fileStateMap[fileName]
	if !ok {
		return
	}

	state.ChangeNum++
	state.AddNum += addNum
	state.DeleteNum += deleteNum
}
