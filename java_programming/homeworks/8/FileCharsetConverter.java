// package cn.edu.ccnu.cs;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

/**
 * 文本文件编码转换实验：从某一种已知编码的文本文件中读取文本，并以另一种编码写入到另一个文件中。
 * 请补充程序以完成相应功能。
 * @author ychang
 *
 */
public class FileCharsetConverter {

	public static boolean convert(String srcFilename, String srcCharset, String destFilename, String destCharset) {
		BufferedReader br = null;
		PrintWriter pw = null;
		String line = null;

		try {
			br = new BufferedReader(new InputStreamReader(new FileInputStream(srcFilename), srcCharset));
			pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(destFilename), destCharset)));

			// 补充完成文本内容的读取和写入
			while ((line = br.readLine()) != null) {
				pw.println(line);
			}

			return true;
		} catch (Exception e) {
			System.out.println("convert error");
		}
		finally {
			try { br.close(); }  catch (Exception e) {}
			try { pw.close(); }  catch (Exception e) {}
		}

		return false;
	}
	public static void main(String[] args) {
		String srcFilename = "GBK编码文档.txt";
		String destFilename = "UTF8编码文档.txt";

		convert(srcFilename, "GBK", destFilename, "UTF-8");

	}

}