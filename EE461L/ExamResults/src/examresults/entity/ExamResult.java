package examresults.entity;

import java.io.Serializable;

import javax.jdo.annotations.IdGeneratorStrategy; 
import javax.jdo.annotations.PersistenceCapable; 
import javax.jdo.annotations.Persistent; 
import javax.jdo.annotations.PrimaryKey; 
import com.google.appengine.api.datastore.Key; 

@PersistenceCapable
public class ExamResult implements Serializable{
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY) 
	private Key id;
	private String name;
	private String exam1Grade;
	private String exam2Grade;

	public ExamResult(){
		
	}
	
	public ExamResult(Key id, String name, String exam1Grade, String exam2Grade){
		
		this.id = id;
		this.name = name;
		this.exam1Grade = exam1Grade;
		this.exam2Grade = exam2Grade;
	}
	
	public Key getId() {
		return id;
	}

	public void setId(Key id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getExam1Grade() {
		return exam1Grade;
	}

	public void setExam1Grade(String exam1Grade) {
		this.exam1Grade = exam1Grade;
	}

	public String getExam2Grade() {
		return exam2Grade;
	}

	public void setExam2Grade(String exam2Grade) {
		this.exam2Grade = exam2Grade;
	}	
	
}