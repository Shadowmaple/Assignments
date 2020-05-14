// package cn.edu.ccnu.cs;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 统计英文单词数目和频次实验：从文本文件中读取英文句子，并统计所出现的英文单词及其出现的次数。
 * 知识点： 文件读取、正则表达式、集合
 * 补充完成程序，以实现相应的功能
 *
 * @author ychang
 *
 */
public class WordCounter {

	public static void main(String[] args) {
		// 定义变量和参数
		String srcFilename = "English.txt";
		Map<String, WordInfo> datas = new HashMap<String, WordInfo>();

		// 统计单词
		FileWordCount(srcFilename, datas);

		// 单词按频次降序排序
		List<WordInfo> words = new ArrayList<WordInfo>(datas.values());
		// 补全程序： 按单词出现的频次tf对words进行排序
		// words.sort((w1, w2) -> (w2.tf - w1.tf));
		Collections.sort(words, (w1, w2) -> (w2.tf - w1.tf));

		// 输出统计结果
		System.out.println("Word               Frequency");
		System.out.println("--------------------------------");
		for (WordInfo wi : words) {
			System.out.printf("%-16s   %5d\n", wi.word, wi.tf);
		}
	}

	/**
	 * 统计文本文件中出现的英文单词及其频次
	 * @param srcFilename   文件名
	 * @param datas         统计结果
	 */
	private static void FileWordCount(String srcFilename, Map<String, WordInfo> datas) {
		BufferedReader br = null;
		String line = null;

		try {
			Pattern p = Pattern.compile("\\b[a-zA-Z-]+\\b");     // 正则表达式  \b 表示单词边界
			br = new BufferedReader(new InputStreamReader(new FileInputStream(srcFilename), "UTF-8"));

			while ((line = br.readLine()) != null)
				count(line, datas, p);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try { br.close(); } catch (Exception e) {}
		}
	}

	/**
	 * 统计某一行的单词
	 * @param line      待统计文本
	 * @param datas     统计结果
	 * @param p         正则表达式
	 */
	private static void count(String line, Map<String, WordInfo> datas, Pattern p) {
		// 补全程序： 统计单词及其频次，并存储在datas中
		Matcher m = p.matcher(line);
		String word;
		while (m.find()) {
			word = m.group();
			if (datas.get(word) != null) {
				datas.get(word).increaseTF();
			} else {
				WordInfo c = new WordInfo(word);
				c.increaseTF();
				datas.put(word, c);
			}
		}
	}

	/**
	 * 说明：内部类是类的一个特殊成员，即类的成员包括：成员变量、成员函数、成员类，所以，其修饰符也是类似的。
	 */
	private static class WordInfo {
		String word;
		int    tf;      // term frequency

		public WordInfo(String word) {
			this.word = word;
			tf = 0;
		}
		public void increaseTF() {
			tf ++;
		}
	}
}