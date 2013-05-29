# Open311 Proxy
A proxy web application intended to keep api_keys secure from HTML clients.

## Background
On our websites we have many web pages where we would like to embed
an Open311 form.  This is instead of setting up a seperate "Open311 forms" web
application that we send the user to.

Challenges with this approach
* To post to Open311, you need an api_key, which should not be included in the markup
* The website shouldn't need to know anything about Open311
* Users should not leave the website when they post

## Intended Solution
The webpage will embed an iframe on the page with src pointing to the
open311-proxy's forms. (Similar to Wufoo)  The open311-proxy can be at any domain.
The user, inside the iframe, is interacting directly with the client proxy.
Because of the iframe, they never leave the webpage.

The open311-proxy will need to look up the api_key for each web page that
embeds the proxy in an iframe.  In essence, we're substituting an
additional client identification system for the api_key system.  It means we
only need to write the web client code once for all the places we want
to put it.  But we can still track each of the places we put it as a
separate api_key according to the Open311 Server.

## Embedding
There are two steps to embed the proxy forms into a webpage.

* As an admin, register the webpage as a client
* Include an iframe and some javascript in the webpage

The open311-proxy embed website will use postMessage() to tell the parent site the new content size.  The parent site should listen for the messages and resize the iframe accordingly

	<script type="text/javascript">
		function handleHeightResponse(e) {
			var iFrame = document.getElementById('open311Client'),
				calcHeight = 0;

			calcHeight = parseInt(e.data + 60);
			if (!calcHeight || calcHeight < 300) { calcHeight = 300; }
			iFrame.height = calcHeight;
		}
		if (window.addEventListener) window.addEventListener('message', handleHeightResponse, false);
	</script>
	<iframe id="open311Client"
			src="http://OPEN311_PROXY/embed?client=XXXX"
			height=\"400\"
			width=\"640\"
			onload=\"this.contentWindow.postMessage('height','http://OPEN311_PROXY');\"></iframe>

