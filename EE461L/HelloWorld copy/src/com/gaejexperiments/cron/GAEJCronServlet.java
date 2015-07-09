package com.gaejexperiments.cron;

import java.io.IOException;
import java.util.Date;
import java.util.Properties;
import java.util.logging.Logger;

import javax.mail.Address;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@SuppressWarnings("serial")
public class GAEJCronServlet extends HttpServlet {
	private static final Logger _logger = Logger.getLogger(GAEJCronServlet.class.getName());
	
	public boolean todayPost(Date date){
		final long MILLIS_PER_DAY = 24 * 60 * 60 * 1000L;
		Date curDate = new Date();
	    boolean moreThanDay = Math.abs(curDate.getTime() - date.getTime()) > MILLIS_PER_DAY;
	    return moreThanDay;
	}
	
	public void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {

		try {
			Properties props = new Properties();
			Session session = Session.getDefaultInstance(props, null);
			try {

				//Retrieve the results
				String strCallResult = "";
				
				List<BlogPost> posts = BlogPostDAO.INSTANCE.getBlogPosts();
				for(int i = 0; i <= posts.size(); i++){
					if(!todayPost(posts[i].getDate)){
						posts.remove(posts[i]);
					}
				} 
				strCallResult = "Title : " + post.getTitle() + "\r\n\n";
				strCallResult += "Body : " + post.getPost() + "\r\n";
				strCallResult += "Posted by : " + post.getUser() + "\r\n";
				strCallResult += "Posted on : " + post.getDate() + "\r\n";				
				strCallResult += "=================================" + "\r\n";
					
				//Send out Email
				MimeMessage outMessage = new MimeMessage(session);
				outMessage.setFrom(new InternetAddress("admin@examresults-461l.appspotmail.com"));
				outMessage.addRecipient(MimeMessage.RecipientType.TO, new InternetAddress(fromAddresses[0].toString()));
				outMessage.setSubject("Your Exam Results");
				outMessage.setText(strCallResult);
				Transport.send(outMessage);
			}
			catch (MessagingException e) { 
				_logger.info("ERROR: Could not send out Email Results response : " + e.getMessage());
			}
		
			_logger.info("Cron Job has been executed");
			
			//Put your logic here
			//BEGIN
			//END
		}
		catch (Exception ex) {
			//Log any exceptions in your Cron Job
		}
	}

	@Override
	public void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		doGet(req, resp);
	}
}