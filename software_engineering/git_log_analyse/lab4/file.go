package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"os"
	"strings"
)

var proFiles = make([]string, 0)

// 获取当前版本项目下所有文件
func GetProFiles() []string {
	file, err := os.Open("./4.7.0_tree_json.data")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	byteValue, err := ioutil.ReadAll(file)
	if err != nil {
		log.Fatal(err)
	}
	var fileData map[string]interface{}
	if err := json.Unmarshal(byteValue, &fileData); err != nil {
		log.Fatal(err)
	}

	recursiveQuery(fileData)

	// for _, item := range ProFiles {
	// 	fmt.Println(item)
	// }
	// fmt.Println(len(ProFiles))

	return proFiles
}

// 递归查询
func recursiveQuery(origin map[string]interface{}) {
	typeValue, ok := origin["type"]
	if !ok || (typeValue != "file" && typeValue != "directory") {
		return
	}

	if typeValue == "file" {
		name := origin["name"].(string)
		proFiles = append(proFiles, strings.TrimLeft(name, "./"))
		return
	}

	contents, ok := origin["contents"]
	if !ok {
		return
	}

	list, ok := contents.([]interface{})
	if !ok {
		log.Fatal("err", "断言错误")
		return
	}

	for _, item := range list {
		recursiveQuery(item.(map[string]interface{}))
	}
}
