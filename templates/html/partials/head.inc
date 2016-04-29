<head>
	<meta http-equiv="X-UA-Compatible" content="IE=edge" />
	<link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/reset.css" />
	<link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/screen.css" />
	<?php
        if (defined('THEME')) {
            $css = BASE_URI.'/'.THEME.'/css/screen.css';
            echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"$css\" />";
        }
	?>
	<title><?php echo isset($this->title) ? self::escape($this->title) : APPLICATION_NAME; ?></title>
</head>
