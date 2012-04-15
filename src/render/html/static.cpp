#include "static.h"
#include "page.h"
#include "../render.h"

using namespace Render;

void Html::quickStart(){
    header("Thanks");
    o << "<div class=\"message\">Now that you've registered you can upload your tracks and follow artists: just click your name at the top right corner of the page.</div>"
         "<div class=\"message\">Don't submit any tracks but your own, though.</div>";
    footer();
}

void Html::faq(){
    header("FAQ");
    o << "<h2>Frequently Asked Questions</h2><div class=\"faq\">"

        "<div><h4>What is this?</h4>"
        "<p>A place for artists to publish their MLP-related music, and get in touch with their audience.</p></div>"

        "<div><h4>Why?</h4>"
        "<p>Because there is no other central repository for MLP music.</p></div>"

        "<div><h4>Why not [INSERT SITE HERE]?</h4>"
        "<p>Because we try to make the publishing and listening process as smooth as can be. No ads, no limits, no downsides.</p></div>"

        "<div><h4>So how do I get on the list of artists? I wanna be one of the cool kids!</h4>"
        "<p><a href=\"/register\">Sign up</a> for an account. Log in, get to your user page, and upload a track, then publish it. <i>Voilà</i>, you're on the list.</p></div>"

        "<div><h4>Do you have an API?</h4>"
        "<p><a href=\"/api\">We do.</a></p>"

        "<div><h4>Who are you anyway?</h4>"
        "<p>We're two developers: <a href=\"/user/1\">codl</a> and <a href=\"/user/2\">fmang</a>. For more information check the <a href=\"/credits\">credits</a>.</p></div>"

        "<div><h4>I've got a question/problem/idea!</h4>"
        "<p>What are you waiting for? Drop us a line at contact@eqbeats.org.</p>"
        "<p>Or <a href=\"http://iris.ponychat.net/?nick=pony_......&channels=eqbeats&prompt=1\">come chat with us</a> in <tt>#eqbeats</tt> on <tt>irc.ponychat.net</tt>. Don't be shy, we're friendly!</p></div>"

        "</div>";
    footer();
}

void Html::credits(){
    header("Credits");
    o << "<h2>Credits</h2><div class=\"credits\">"
        "<h4>Staff</h4>"
        "<ul>"
            "<li><a href=\"/user/1\">codl</a></li>"
            "<li><a href=\"/user/2\">fmang</a></li>"
        "</ul>"
        "<h4>Support</h4>"
        "<ul>"
            "<li><a href=\"/user/3\">AspectOfTheStorm</a></li>"
            "<li><a href=\"/user/6\">Makkon</a></li>"
            "<li><a href=\"/user/68\">Karai</a></li>"
        "</ul>"
        "<h4>Design</h4>"
        "<ul>"
            "<li><a href=\"http://www.slt.fr\">SLT</a> - Logo</li>"
            "<li><a href=\"http://blackm3sh.deviantart.com/art/Rarity-Filly-203377463\">BlackM3sh</a> - Filly Rarity</li>"
            "<li><a href=\"http://p.yusukekamiyamane.com/\">Yusuke Kamiyamane</a> - Fugue icon set</li>"
        "</ul></div>";
    footer();
}

void Html::apiDoc(){
    header("API");
    o << "<div id=\"api\">"
         "<h2>API</h2>"
         "<h3>Quickstart</h3>"
         "<p>We have a read-only JSON/JSONp api to access user and track data.<br/>"
         "Just add <tt>/json</tt> to most urls to get a JSON representation of that page.<br/>"
         "Adding a <tt>jsonp</tt> parameter will insert the JSON data as an argument to a function named by the <tt>jsonp</tt> parameter. It can then be run through eval() in javascript.<br/>"
         "Compare <a href=\"http://eqbeats.org/tracks/latest/json\">/tracks/latest/json</a> and <a href=\"http://eqbeats.org/tracks/latest/json?jsonp=myCallback\">/tracks/latest/json?jsonp=myCallback</a>.</p>"
         "<h3 id=\"user\">User object</h3>"
         "<table>"
            "<tr><td><tt>id</tt></td><td>Unique numerical id for this user.</td></tr>"
            "<tr><td><tt>name</tt></td><td>User name.</td></tr>"
            "<tr><td><tt>description</tt></td><td>User's description of themselves, unescaped. This member will not exist if there is no description.</td></tr>"
            "<tr><td><tt>html_description</tt></td><td>User's description of themselves, in HTML. This member will not exist if there is no description.</td></tr>"
            "<tr><td><tt>tracks</tt></td><td>An array of <a href=\"#track\">Track objects</a> for all tracks published by the user.</td></tr>"
            "<tr><td><tt>link</tt></td><td>Permalink to the user's page.</td></tr>"
         "</table>"
         "<pre>{<br/>"
         "  \"id\": 123,<br/>"
         "  \"name\": \"Foo Bar\",<br/>"
         "  \"description\": \"Just some dude making music.\",<br/>"
         "  \"tracks\": [{\"id\": 456, ...}, ...],<br/>"
         "  \"link\": \"http://eqbeats.org/user/123\"<br/>"
         "}</pre>"
         "<h3 id=\"track\">Track object</h3>"
         "<table>"
            "<tr><td><tt>id</tt></td><td>Unique numerical id for the track.</td></tr>"
            "<tr><td><tt>title</tt></td><td>Track title.</td></tr>"
            "<tr><td><tt>description</tt></td><td>Track notes, unescaped. This member will not exist if there are no notes.</td></tr>"
            "<tr><td><tt>html_description</tt></td><td>Track notes, in HTML. This member will not exist if there are no notes.</td></tr>"
            "<tr><td><tt>artist</tt></td><td>An <a href=\"#user\">user object</a> for the artist (excluding the track array).</td></tr>"
            "<tr><td><tt>link</tt></td><td>Permalink to the track's page.</td></tr>"
            "<tr><td><tt>download</tt></td><td>An object with a member for each downloadable file format and the permalink to the file as their value. Currently, available formats are mp3 and vorbis.</td></tr>"
         "</table>"
         "<pre>{<br/>"
         "  \"id\": 456,<br/>"
         "  \"title\": \"Baz Quux\",<br/>"
         "  \"description\": \"A track about bazing while you quux.\",<br/>"
         "  \"artist\": {\"id\": 123, \"name\": \"Foo Bar\",...}<br/>"
         "  \"link\": \"http://eqbeats.org/track/456\",<br/>"
         "  \"download\": {\"mp3\":\"http://eqbeats.org/track/456/mp3\",<br/>"
         "               \"vorbis\":\"http://eqbeats.org/track/456/vorbis\"}<br/>"
         "}</pre>"
         "<h3>Resources</h3>"
         "<table>"
         "<tr><td><tt>/user/<var>{id}</var>/json</tt></td><td>Retrieves one <a href=\"#user\">user object</a></td></tr>"
         "<tr><td><tt>/user/search/json?q=<var>{query}</var></tt></td><td>Retrieves a list of users matching the query</td></tr>"
         "<tr><td><tt>/artists/json</tt></td><td>Retrieves a list of all artists (as shortened artists objects, without their tracks)</td></tr>"
         "<tr><td><tt>/track/<var>{id}</var>/json</tt></td><td>Retrieves one <a href=\"#track\">track object</a></td></tr>"
         "<tr><td><tt>/tracks/search/json?q=<var>{query}</var></tt></td><td>Retrieves a list of tracks matching the query</td></tr>"
         "<tr><td><tt>/tracks/latest/json</tt></td><td>Retrieves a list of the latest 50 tracks</td></tr>"
         "<tr><td><tt>/tracks/featured/json</tt></td><td>Retrieves a list of the latest 50 featured tracks</td></tr>"
         "<tr><td><tt>/tracks/random/json</tt></td><td>Retrieves a list of 50 random tracks</td></tr>"
         "</table>"
         "</div>"
         ;
    footer();
}
