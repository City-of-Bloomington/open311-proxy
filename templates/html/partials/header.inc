<header>
    <div class="container">
        <h1><a href="<?= BASE_URI; ?>"><?= self::escape(APPLICATION_NAME); ?></a></h1>
        <div class="utilityBar">
        <?php
            $this->addToAsset('scripts', BASE_URI.'/js/menus.js');

            $this->_include('partials/panel-widgets/User_menu.inc');
            $this->_include('partials/panel-widgets/Administrator_menu.inc');
        ?>
        </div>
    </div>
</header>
