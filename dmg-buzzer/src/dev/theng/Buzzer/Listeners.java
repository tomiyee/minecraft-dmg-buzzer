package dev.theng.Buzzer;

import java.net.URL;

import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.entity.EntityDamageEvent;

import sun.net.www.protocol.http.HttpURLConnection;

public class Listeners implements Listener {

	@EventHandler
	public void onPlayerDamage(EntityDamageEvent e) {
		if (e.getEntity() instanceof Player) {
			Player p = (Player) e.getEntity();
			try {
				// Send a Post Request to the web server
				URL url = new URL(Main.WEB_SERVER_URL + "/hurt");
				HttpURLConnection httpClient = (HttpURLConnection) url.openConnection();
				httpClient.setRequestMethod("POST");
				httpClient.getResponseCode();
				// sends a message to the player who took damage
				p.sendMessage("You took damage!");
			}
			catch (Exception err) {
				System.out.println(err);
				p.sendMessage("Something went wrong making the POST Request.");
			}
		}
	}
}
