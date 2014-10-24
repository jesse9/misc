/**
 * @project:	zillow
 * @package:	com.zillow.test
 * @filename:	TestSWTBrowser.java
 * @author:		Xing Zhou
 * @date:		2014年10月23日
 * @time:		下午10:45:43
 */
package com.zillow.test;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import org.eclipse.swt.browser.*;

/**
 * @author jesse
 *
 */
public class TestSWTBrowser {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Display display = new Display();
		final Shell shell = new Shell(display);
		GridLayout gridLayout = new GridLayout();
		gridLayout.numColumns = 3;
		shell.setLayout(gridLayout);
		ToolBar toolbar = new ToolBar(shell, SWT.NONE);
		ToolItem itemBack = new ToolItem(toolbar, SWT.PUSH);
		itemBack.setText("Back");
		ToolItem itemForward = new ToolItem(toolbar, SWT.PUSH);
		itemForward.setText("Forward");
		ToolItem itemStop = new ToolItem(toolbar, SWT.PUSH);
		itemStop.setText("Stop");
		ToolItem itemRefresh = new ToolItem(toolbar, SWT.PUSH);
		itemRefresh.setText("Refresh");
		ToolItem itemGo = new ToolItem(toolbar, SWT.PUSH);
		itemGo.setText("Go");

		GridData data = new GridData();
		data.horizontalSpan = 3;
		toolbar.setLayoutData(data);

		Label labelAddress = new Label(shell, SWT.NONE);
		labelAddress.setText("Address");

		final Text location = new Text(shell, SWT.BORDER);
		data = new GridData();
		data.horizontalAlignment = GridData.FILL;
		data.horizontalSpan = 2;
		data.grabExcessHorizontalSpace = true;
		location.setLayoutData(data);
		final Browser browser;
		try {
			browser = new Browser(shell, SWT.NONE);
		} catch (SWTError e) {
			System.out.println("Could not instantiate Browser: "
					+ e.getMessage());
			display.dispose();
			return;
		}
		data = new GridData();
		data.horizontalAlignment = GridData.FILL;
		data.verticalAlignment = GridData.FILL;
		data.horizontalSpan = 3;
		data.grabExcessHorizontalSpace = true;
		data.grabExcessVerticalSpace = true;
		browser.setLayoutData(data);

		final Label status = new Label(shell, SWT.NONE);
		data = new GridData(GridData.FILL_HORIZONTAL);
		data.horizontalSpan = 2;
		status.setLayoutData(data);

		final ProgressBar progressBar = new ProgressBar(shell, SWT.NONE);
		data = new GridData();
		data.horizontalAlignment = GridData.END;
		progressBar.setLayoutData(data);

		/* event handling */
		Listener listener = new Listener() {
			@Override
			public void handleEvent(Event event) {
				ToolItem item = (ToolItem) event.widget;
				String string = item.getText();
				if (string.equals("Back"))
					browser.back();
				else if (string.equals("Forward"))
					browser.forward();
				else if (string.equals("Stop"))
					browser.stop();
				else if (string.equals("Refresh"))
					browser.refresh();
				else if (string.equals("Go"))
					browser.setUrl(location.getText());
			}
		};
		browser.addProgressListener(new ProgressListener() {
			@Override
			public void changed(ProgressEvent event) {
				if (event.total == 0)
					return;
				int ratio = event.current * 100 / event.total;
				progressBar.setSelection(ratio);
			}

			@Override
			public void completed(ProgressEvent event) {
				progressBar.setSelection(0);
			}
		});
		browser.addStatusTextListener(new StatusTextListener() {
			@Override
			public void changed(StatusTextEvent event) {
				status.setText(event.text);
			}
		});
		browser.addLocationListener(new LocationListener() {
			@Override
			public void changed(LocationEvent event) {
				if (event.top)
					location.setText(event.location);
			}

			@Override
			public void changing(LocationEvent event) {
			}
		});
		itemBack.addListener(SWT.Selection, listener);
		itemForward.addListener(SWT.Selection, listener);
		itemStop.addListener(SWT.Selection, listener);
		itemRefresh.addListener(SWT.Selection, listener);
		itemGo.addListener(SWT.Selection, listener);
		location.addListener(SWT.DefaultSelection, new Listener() {
			@Override
			public void handleEvent(Event e) {
				browser.setUrl(location.getText());
			}
		});
		
		browser.addProgressListener(new ProgressListener() {
			@Override
			public void changed(ProgressEvent event) {
				try {
					Double length = (Double) browser
							.evaluate("return document.getElementById('search-results').getElementsByTagName('article').length;");
					System.out.println("length: " + length);
					for (int i = 0; i < length; ++i) {
						String html = (String)browser.evaluate("return document.getElementById('search-results').getElementsByTagName('article')[" + i+"].id");
						System.out.println(i + ": " + html);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
			@Override
			public void completed(ProgressEvent event) {
				System.out.println("completed");
			}
		});

		shell.open();
		browser.setUrl("http://www.zillow.com/homes/for_sale/house,condo,apartment,duplex,townhouse_type/2-_beds/days_sort/40.32551,-74.572406,40.286957,-74.683986_rect/13_zm/0_mmm/");

		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		display.dispose();
	}

}
