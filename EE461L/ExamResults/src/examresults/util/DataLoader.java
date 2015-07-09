package examresults.util;

import examresults.dao.ExamResultDAO;

public class DataLoader {
	
	public static void loadData() {
		ExamResultDAO.INSTANCE.add("12345", "test student", "67", "76");	
	}
}