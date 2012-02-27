<nav>
	<a href="<?php echo BASE_URL; ?>">Home</a>
	<?php
		if (isset($_SESSION['USER'])) {
			echo '<a href="'.BASE_URL.'/login/logout.php">Logout</a>';
		}
		else {
			echo "
			<a href=\"".BASE_URL."/login?return_url=$_SERVER[REQUEST_URI]\">
				Login
			</a>
			";
		}
	?>
</nav>
