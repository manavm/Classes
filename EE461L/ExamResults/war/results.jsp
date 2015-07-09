<%@ page import="examresults.entity.*" %> 
<html> 
<head> 
<meta http-equiv="content-type" content="text/html; charset=UTF-8"> 
<title>Exam Results</title> 
</head> 
<body> 
	<h1>Welcome to your exam results!</h1><hr/> 
	<% 
	ExamResult result = (ExamResult)session.getAttribute("result"); 
	if (result != null){ 
	%> 
	<table> 
		<tr> 
			<td style="font-weight:bold;">ID Number:</td> 
			<td><%=result.getId() %></td> 
		</tr> 
	</table> 
<% 
} else { 
%> 
	<h3>We could not provide you with any results.</h3> 
<% 
} 
%> 
	<hr/><a href="ExamResults.html">Back to Home</a> 
</body> 
</html>