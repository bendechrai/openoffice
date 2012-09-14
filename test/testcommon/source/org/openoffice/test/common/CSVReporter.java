package org.openoffice.test.common;

import java.io.File;
import java.util.Map.Entry;
import java.util.Set;

import org.junit.Ignore;
import org.junit.runner.Description;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.runner.notification.RunListener;

public class CSVReporter extends RunListener {

	private File reportDir = Testspace.getFile("output/result");

	private File file = null;

	private String testClassName = null;

	private long suiteStart = 0;

	private long failures = 0;

	private long errors = 0;

	private long tests = 0;

	private long ignored = 0;

	private long testStart = 0;

	@Override
	public void testStarted(Description description) throws Exception {
		System.out.println("testStarted");
		if (!description.getClassName().equals(testClassName)) {
			finishSuite();
			startSuite(description);
		}
		

	}

	@Override
	public void testAssumptionFailure(Failure failure) {

	}

	@Override
	public void testFailure(Failure failure) throws Exception {
		System.out.println("testFailure");
		if (failure.getException() instanceof AssertionError) {
			failures++;
		} else {
			errors++;
		}
	}

	@Override
	public void testFinished(Description description) throws Exception {
		System.out.println("testFinished");
		tests++;
	}

	@Override
	public void testIgnored(Description description) throws Exception {
		testStarted(description);
		System.out.println("testIgnored");
		ignored++;
		Ignore ignore = description.getAnnotation(Ignore.class);
		testFinished(description);
	}

	@Override
	public void testRunFinished(Result result) throws Exception {
		System.out.println("testRunFinished");
		finishSuite();
	}

	@Override
	public void testRunStarted(Description description) throws Exception {
		System.out.println("testRunStarted");
	}

	private void startSuite(Description description) {
		testClassName = description.getClassName();
		suiteStart = System.currentTimeMillis();
		failures = 0;
		errors = 0;
		tests = 0;
		ignored = 0;

		file = new File(reportDir, testClassName + ".csv");
	}

	private void finishSuite() {
		if (testClassName == null)
			return;

	
		Set<Entry<Object, Object>> entries = System.getProperties().entrySet();
		for (Entry<Object, Object> e : entries) {
//			Element prop = doc.createElement("property");
//			prop.setAttribute("name", "" + e.getKey());
//			prop.setAttribute("value", "" + e.getValue());
//			props.appendChild(prop);
		}

		store();
	}

	private void store() {

	}

}
