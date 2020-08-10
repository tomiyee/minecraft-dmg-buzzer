package dev.theng.Buzzer;

import java.net.HttpURLConnection;
import java.net.URL;

import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Player;
import org.bukkit.plugin.java.JavaPlugin;

public class Main extends JavaPlugin{

	public static String WEB_SERVER_URL = "http://73.231.51.90";

	@Override
	public void onEnable () {
		// startup, reload, plugin reloads
		getServer().getPluginManager().registerEvents(new Listeners(), this);
	}

	public boolean onCommand (CommandSender sender, Command cmd, String label, String[] args) {
		if (label.equalsIgnoreCase("takeDamage")) {
			if (sender instanceof Player) {
				Player p = (Player) sender;
				// test sending an HTTP request
				try {
					// Send a Post Request to the web server
					URL url = new URL(WEB_SERVER_URL + "/hurt");
					HttpURLConnection httpClient = (HttpURLConnection) url.openConnection();
					httpClient.setRequestMethod("POST");
					httpClient.getResponseCode();
				}
				catch (Exception e) {
					System.out.println(e);
					p.sendMessage("An error went down.");
				}
				return true;
			}
		}
		return false;
	}
}
