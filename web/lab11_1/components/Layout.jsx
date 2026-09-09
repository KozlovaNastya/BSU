import React from 'react';
import { Link } from 'react-router-dom';
import { styled } from '@mui/material/styles';
import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemText from '@mui/material/ListItemText';
import Paper from '@mui/material/Paper';

const Offset = styled('div')(({ theme }) => theme.mixins.toolbar);

const Layout = ({ children }) => {
  const navItems = [
    { path: '/example', label: 'Example' },
    { path: '/regions', label: 'Regions' },
    { path: '/mysearch', label: 'MySearch' },
  ];

  return (
    <div>
      <AppBar position="fixed">
        <Toolbar>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
            React Lab SPA
          </Typography>
        </Toolbar>
      </AppBar>
      <Offset />

      <Grid container spacing={2} sx={{ padding: 2 }}>
        <Grid item xs={12} sm={3}>
          <Paper elevation={3} sx={{ padding: 2 }}>
            <Typography variant="h6" gutterBottom>
              Навигация
            </Typography>
            <List>
              {navItems.map((item) => (
                <ListItem key={item.path} disablePadding>
                  <ListItemButton component={Link} to={item.path}>
                    <ListItemText primary={item.label} />
                  </ListItemButton>
                </ListItem>
              ))}
            </List>
          </Paper>
        </Grid>

        <Grid item xs={12} sm={9}>
          <Paper elevation={3} sx={{ padding: 3, minHeight: '400px' }}>
            {children} {/* Вместо Outlet */}
          </Paper>
        </Grid>
      </Grid>
    </div>
  );
};

export default Layout;