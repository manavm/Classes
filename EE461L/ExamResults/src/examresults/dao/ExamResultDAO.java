package examresults.dao;

import java.util.List; 
import javax.jdo.PersistenceManager; 
import javax.jdo.Query; 
import com.google.appengine.api.datastore.Key; 
import com.google.appengine.api.datastore.KeyFactory; 
import examresults.entity.ExamResult; 
import examresults.services.PMF; 

public enum ExamResultDAO { 
INSTANCE;

public List<ExamResult> getExamResults() { 
	List<ExamResult> examResults; 
	PersistenceManager pm = PMF.get().getPersistenceManager(); 
	Query query = pm.newQuery(ExamResult.class); 
	try{ 
		examResults = (List<ExamResult>) query.execute();
	} 
	finally{ 
		pm.close(); 
	} 
	return (examResults); 
}

public void deleteAll(){ 
	List<ExamResult> examResults; 
	PersistenceManager pm = 
			PMF.get().getPersistenceManager(); 
	Query query = pm.newQuery(ExamResult.class); 
	try{ 
		examResults = (List<ExamResult>) query.execute(); 
		pm.deletePersistentAll(examResults); 
	} 
	finally{ 
		pm.close(); 
	} 
}

public String add(String idNumber, String studentName, 
		String exam1Grade, String exam2Grade){ 
	Key key = 
			KeyFactory.createKey(ExamResult.class.getSimpleName(), idNumber); 
	ExamResult newResult = new ExamResult(); 
	newResult.setId(key); 
	newResult.setName(studentName); 
	newResult.setExam1Grade(exam1Grade); 
	newResult.setExam2Grade(exam2Grade); 
	synchronized(this){ 
		PersistenceManager pm = PMF.get().getPersistenceManager(); 
		try{ 
			pm.makePersistent(newResult); 
		} 
		finally{ 
			pm.close(); 
		} 
	} 
	return (newResult.getId().getName()); 
}

public void update(String idNumber, String studentName, 
		String exam1Grade, String exam2Grade){ 
	ExamResult result; 
	synchronized(this){ 
		PersistenceManager pm = PMF.get().getPersistenceManager(); 
		Key k = 
				KeyFactory.createKey(ExamResult.class.getSimpleName(), idNumber); 
		try{ 
			result = pm.getObjectById(ExamResult.class, k); 
			result.setName(studentName); 
			result.setExam1Grade(exam1Grade); 
			result.setExam2Grade(exam2Grade); 
		} 
		finally{ 
			pm.close(); 
		} 
	} 
}

public void remove(String idNumber){ 
	PersistenceManager pm = 
			PMF.get().getPersistenceManager(); 
	Key k = 
			KeyFactory.createKey(ExamResult.class.getSimpleName(), 
					idNumber); 
	ExamResult result; 
	try{ 
		result = pm.getObjectById(ExamResult.class, k); 
		pm. deletePersistent(result); 
	} 
	finally{ 
		pm.close(); 
	} 
} 

public ExamResult getExamResult(String idNumber){ 
	PersistenceManager pm = 
			PMF.get().getPersistenceManager(); 
	Key k = 
			KeyFactory.createKey(ExamResult.class.getSimpleName(), 
					idNumber); 
	ExamResult result = null; 
	try{ 
		result = pm.getObjectById(ExamResult.class, k); 
	} 
	finally{ 
		pm.close(); 
	} 
	return result; 
}


}