package examresults;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import examresults.dao.ExamResultDAO;
import examresults.entity.ExamResult;

public class ExamResultsServlet extends HttpServlet{
	
	private static final Logger _logger = 
			Logger.getLogger(ExamResultsServlet.class.getName());

	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException{ 
		//extract the input parameters 
		String idNumber = req.getParameter("idnumber"); 
		_logger.info("Received a requst for id number: " + idNumber); 
		try{ 
			if(idNumber == null) throw new Exception("Must provide id number!"); 
			if(!idNumber.isEmpty()){ 
				//retrieve the results (currently just chuck back some dummy results) 
//				ExamResult dummyResult = getDummyResult(idNumber); 
				ExamResult result = 
						ExamResultDAO.INSTANCE.getExamResult(idNumber); 
				req.getSession().setAttribute("result", result); 
				resp.sendRedirect("results.jsp"); 
			} 
			else throw new Exception("Must provide id number!"); 
		} 
		catch (Exception e) { 
			String logMsg = "Exception in processing request: " + e.getMessage(); 
			_logger.log(Level.INFO, logMsg); 
			throw new IOException(logMsg); 
		} 
	}

//	private ExamResult getDummyResult(String idNumber){ 
//		ExamResult toReturn = new ExamResult(); 
////		toReturn.setId(idNumber); 
//		toReturn.setName("Christine Julien"); 
//		toReturn.setExam1Grade("100"); 
//		toReturn.setExam2Grade("99"); 
//		return toReturn; 
//	} 
	
}