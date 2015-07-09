package helloworld.util;

import java.util.Date;

import com.google.appengine.api.users.User;

import helloworld.dao.BlogPostDAO;
import helloworld.entity.BlogPost;

public class DataLoader {
	
	public static void loadData(User user, Date date) {
		BlogPostDAO.INSTANCE.addBlogPost("12345", "test student", user, date);	
	}
}